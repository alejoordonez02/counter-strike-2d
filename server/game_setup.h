#ifndef SERVER_GAME_SETUP_H
#define SERVER_GAME_SETUP_H

#include "common/maploader.h"
#include "game_loop.h"
#include "model/equipment.h"
#include "model/game.h"
#include "model/player.h"
#include "model/random.h"
#include "model/structure.h"
#include "model/weapons.h"

#define TICK_RATE 20
#define COMMANDS_PER_TICK 30
#define ROUNDS 15
#define ROUND_TIME 600
#define TIME_OUT 10
#define PLAYER_MAX_VELOCITY 90
#define PLAYER_ACCELERATION 360
#define PLAYER_RADIUS 10
#define PLAYER_STARTING_MONEY 800
#define PLAYER_MAX_HEALTH 100

struct GameConfig {
    // Configuración general del juego
    int tick_rate = 64;
    int rounds = 15;
    int round_time = 600;  // en segundos
    int time_out = 10;     // en segundos
    float player_max_velocity = 15.0f;
    float player_acceleration = 1000.0f;
    float player_radius = 0.5f;
    int player_starting_money = 800;
    int player_max_health = 100;
};

/*
 * Map config
 * */
static inline std::shared_ptr<Map> get_map() {
    auto map = std::make_shared<Map>();
    MapLoader map_loader;
    MapData map_data =
        map_loader.loadMapData("tests/client/prueba_mapa_mod.yaml");
    for (auto b : map_data.blocks)
        map->add_collidable(
            std::make_shared<Structure>(Position(b.x, b.y), 32));

    return map;
}

/*
 * Game config
 * */
static inline float get_rounds() { return ROUNDS; }
static inline float get_round_time() { return ROUND_TIME; }
static inline float get_time_out() { return TIME_OUT; }

/*
 * Player config
 * */
static int id = -1;
static inline int get_player_id() {
    id++;
    return id;
}

static inline Position get_starting_position() {
    return Position(Random::get(-30, 30), Random::get(-30, 30));
}

static inline std::unique_ptr<Equipment> get_starting_equipment() {
    return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                       std::make_unique<Glock>(),
                                       std::make_unique<Knife>(), 0);
};

static inline float get_player_max_velocity() { return PLAYER_MAX_VELOCITY; }
static inline float get_player_acceleration() { return PLAYER_ACCELERATION; }
static inline float get_player_radius() { return PLAYER_RADIUS; }
static inline int get_player_starting_money() { return PLAYER_STARTING_MONEY; }
static inline int get_player_max_health() { return PLAYER_MAX_HEALTH; }

class GameSetup {
public:
    /*
     * Game loop config
     * */
    static inline int get_tick_rate() { return TICK_RATE; }
    static inline int get_commands_per_tick() { return COMMANDS_PER_TICK; }

    static Game create_game() {
        return Game(get_map(), get_rounds(), get_round_time(), get_time_out());
    }

    // Player(int id, Position pos, std::unique_ptr<Equipment>&& equipment,
    //        float max_velocity, float acceleration, float radius, int money,
    //        int health);
    static std::shared_ptr<Player> create_player(std::shared_ptr<Map> map) {
        auto player = std::make_shared<Player>(
            get_player_id(), get_starting_position(), get_starting_equipment(),
            map, get_player_max_velocity(), get_player_acceleration(),
            get_player_radius(), get_player_starting_money(),
            get_player_max_health());
        return player;
    }
};

#endif
