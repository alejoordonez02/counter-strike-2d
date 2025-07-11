#include "game.h"

#include <utility>

#include "common/network/connection.h"
#include "world/world.h"

/*
 * Add players
 * */
void Game::add_player(Connection&& con, TeamName team) {
    std::unique_lock<std::mutex> lck(m);
    pending.push_back(std::make_pair(std::move(con), team));
}

void Game::add_pending_players() {
    std::vector<std::pair<Connection, TeamName>> tmp;

    {
        std::unique_lock<std::mutex> lck(m);
        if (pending.empty()) return;
        tmp = std::move(pending);
        pending.clear();
    }

    for (auto& t : tmp) {
        std::shared_ptr<Player> p = world.add_player(t.second);
        auto h = std::make_unique<PlayerHandler>(std::move(t.first), p);
        h->start();
        players.push_back(std::move(h));
    }
}

/*
 * Constructor
 * */
Game::Game(World&& world, int tick_rate, int commands_per_tick):
    world(std::move(world)), tick_duration(Ms(1000) / tick_rate),
    commands_per_tick(commands_per_tick) {}

/*
 * Game loop
 * */
void Game::run() {
    auto t1 = Clock::now();
    float elapsed_seconds = Duration(tick_duration).count();
    world.start();  // TODO: ésto lo debería poder hacer el user
    while (should_keep_running()) {
        if (world.has_ended()) stop();
        add_pending_players();

        auto snapshot = world.get_snapshot();
        for (auto& p : players) p->send_snapshot(snapshot);

        for (int i = 0; i < commands_per_tick; i++)
            for (auto& p : players) p->play();

        world.update(elapsed_seconds);
        auto t2 = Clock::now();
        auto work_time = t2 - t1;
        auto rest_time = tick_duration - work_time;
        if (rest_time.count() > 0) {
            std::this_thread::sleep_for(rest_time);
            t1 += tick_duration;
        }
    }
}

int Game::get_tt_count() { return world.get_tt_count(); }

int Game::get_ct_count() { return world.get_ct_count(); }

bool Game::is_joinable() {
    return !(world.team_is_full(TeamName::TERRORIST) &&
            world.team_is_full(TeamName::COUNTER_TERRORIST));
}