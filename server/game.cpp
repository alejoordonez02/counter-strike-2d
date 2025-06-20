#include "game.h"

#include "common/network/connection.h"
#include "world/equipment/equipment.h"
#include "world/equipment/weapons.h"
#include "world/physics/structure.h"
#include "world/player_factory.h"
#include "world/random.h"
#include "world/world.h"

/*
 * Add pending players
 * Ojo! acá hay race condition
 * */
void Game::add_pending_players() {
    std::vector<Connection> tmp;

    {
        std::unique_lock<std::mutex> lck(m);
        if (pending.empty()) return;
        tmp = std::move(pending);
        pending.clear();
    }

    for (auto& con : tmp) {
        std::shared_ptr<Player> p = world.add_player();
        auto h = std::make_unique<PlayerHandler>(std::move(con), p);
        h->start();
        players.push_back(std::move(h));
    }
}

/*
 * éstas funciones son temp, ahora las estoy usando porque no me quiero poner a
 * codear terrorists y counter terrorists, pero en realidad esas dos clases no
 * reciben por parámetro el equipment ni la posición inicial, si no que tienen
 * lógica para inicializar esos atributos. Esto vuela (el factory se queda no)
 * */
static inline Position get_starting_position() {
    return Position(Random::get(-30, 30), Random::get(-30, 30));
}

static inline std::unique_ptr<Equipment> get_starting_equipment() {
    return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                       std::make_unique<Glock>(),
                                       std::make_unique<Knife>(), 0);
};

PlayerFactory Game::create_player_factory(std::shared_ptr<Map> map,
                                          const WorldConfig& config) {
    return [map, config](int id) {
        // Aquí podés definir la lógica de posición, equipamiento, etc.
        Position pos = get_starting_position();
        auto equipment = get_starting_equipment();
        return std::make_shared<Player>(
            id, pos, std::move(equipment), map, config.player_max_velocity,
            config.player_acceleration, config.player_radius,
            config.player_starting_money, config.player_max_health);
    };
}

/*
 * Constructor
 * */
Game::Game(const GameConfig& config):
    world([&config, this] {
        auto map = std::make_shared<Map>();
        for (const auto& block : config.map.blocks)
            if (block.type == "Solid")
                map->add_collidable(std::make_shared<Structure>(
                    Position(block.x, block.y), 32));

        PlayerFactory factory = create_player_factory(map, config.world);
        return World(std::move(map), config.world.rounds,
                     config.world.round_time, config.world.time_out,
                     std::move(factory));
    }()),
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
void Game::add_player(Connection&& con) {
    std::unique_lock<std::mutex> lck(m);
    pending.push_back(std::move(con));
}
