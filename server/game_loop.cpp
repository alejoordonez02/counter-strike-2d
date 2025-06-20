#include "game_loop.h"

#include "common/network/connection.h"
#include "game.h"
#include "game_setup.h"

/*
 * Add pending players
 * Ojo! acá hay race condition
 * */
void GameLoop::add_pending_players() {
    std::vector<Connection> tmp;

    {
        std::unique_lock<std::mutex> lck(m);
        if (pending.empty()) return;
        tmp = std::move(pending);
        pending.clear();
    }

    for (auto& con : tmp) {
        std::shared_ptr<Player> p = game.add_player();
        auto h = std::make_unique<PlayerHandler>(std::move(con), p);
        h->start();
        players.push_back(std::move(h));
    }
}

/*
 * Constructor
 * */
GameLoop::GameLoop():
    game(GameSetup::create_game()),
    tick_duration(Ms(1000) / GameSetup::get_tick_rate()),
    commands_per_tick(GameSetup::get_commands_per_tick()) {}

/*
 * Game loop
 * */
void GameLoop::run() {
    auto t1 = Clock::now();
    float elapsed_seconds = Duration(tick_duration).count();
    while (should_keep_running()) {
        add_pending_players();

        auto snapshot = game.get_snapshot();
        for (auto& p : players) p->send_snapshot(snapshot);

        for (int i = 0; i < commands_per_tick; i++)
            for (auto& p : players) p->play();

        game.update(elapsed_seconds);
        auto t2 = Clock::now();
        auto work_time = t2 - t1;
        auto rest_time = tick_duration - work_time;
        if (rest_time.count() > 0) {
            std::this_thread::sleep_for(rest_time);
            t1 += tick_duration;
        }
    }
}

/*
 * Add new player
 * */
void GameLoop::add_player(Connection&& con) {
    std::unique_lock<std::mutex> lck(m);
    pending.push_back(std::move(con));
}
