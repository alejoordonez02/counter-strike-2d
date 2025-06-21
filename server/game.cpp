#include "game.h"

#include <stdexcept>

#include "common/network/connection.h"
#include "world/physics/structure.h"
#include "world/player_factory.h"
#include "world/world.h"

/*
 * Ésto probablemente termine quedando en algún World creator, no me estaría
 * logrando decidir en cuanto a ésta responsabilidad, algunas opciones me
 * desacoplan una cosa y me acoplan otra y así
 * */
World Game::create_world(const GameConfig& config) {
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::vector<Structure> bomb_site;
    std::vector<Position> tt_spawn;
    std::vector<Position> ct_spawn;
    for (const auto& block : config.map.blocks) {
        if (block.type == "Solid")
            collidables.push_back(
                std::make_shared<Structure>(Position(block.x, block.y), 32));

        else if (block.type == "Plantable")
            bomb_site.push_back(Structure(Position(block.x, block.y), 32));

        else if (block.type == "TSpawn")
            tt_spawn.push_back(Position(block.x, block.y));

        else if (block.type == "CtSpawn")
            ct_spawn.push_back(Position(block.x, block.y));
    }

    if (tt_spawn.empty())
        throw std::runtime_error("Config error: no tt spawn in config file");
    if (ct_spawn.empty())
        throw std::runtime_error("Config error: no ct spawn in config file");

    auto map =
        std::make_shared<Map>(collidables, bomb_site, tt_spawn, ct_spawn);
    return World(std::move(map), config.world.rounds, config.world.round_time,
                 config.world.time_out, PlayerFactory(map, config.world));
}

/*
 * Add pending players
 * */
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
Game::Game(const GameConfig& config):
    world(create_world(config)),
    tick_duration(Ms(1000) / config.loop.tick_rate),
    commands_per_tick(config.loop.commands_per_tick) {}

/*
 * Game loop
 * */
void Game::run() {
    auto t1 = Clock::now();
    float elapsed_seconds = Duration(tick_duration).count();
    while (should_keep_running()) {
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

/*
 * Add new player
 * */
void Game::add_player(Connection&& con, TeamName team) {
    std::unique_lock<std::mutex> lck(m);
    pending.push_back(std::make_pair(std::move(con), team));
}
