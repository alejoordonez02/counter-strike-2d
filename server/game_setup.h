#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "game_loop.h"
#include "map.h"
#include "model/equipment.h"
#include "network/client_handler.h"
#include "player.h"
#include "player_handler.h"
#include "random.h"
#include "weapons.h"

#define TICK_RATE 20
#define ROUNDS 15
#define ROUND_TIME 600
#define TIME_OUT 10
#define PLAYER_MAX_VELOCITY 15.0f
#define PLAYER_ACCELERATION 1000.0f
#define PLAYER_RADIUS 0.5f
#define PLAYER_STARTING_MONEY 800
#define PLAYER_MAX_HEALTH 100

/*
 * GameSetup usa el parser para leer la config e instanciar el juego. Estos get
 * vendrían a ser los retornos del parser
 * */
static inline std::shared_ptr<Map> get_map() {
    Map map;
    return std::make_shared<Map>();
}

static inline Position get_starting_position() {
    return Position(Random::get(-30, 30), Random::get(-30, 30));
}

static inline std::unique_ptr<Equipment> get_starting_equipment() {
    return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                       std::make_unique<Glock>(),
                                       std::make_unique<Knife>(), 0);
};

static inline int get_tick_rate() { return TICK_RATE; }

static inline float get_rounds() { return ROUNDS; }

static inline float get_round_time() { return ROUND_TIME; }

static inline float get_time_out() { return TIME_OUT; }

static int id = -1;
static inline int get_player_id() {
    id++;
    return id;
}

static inline float get_player_max_velocity() { return PLAYER_MAX_VELOCITY; }

static inline float get_player_acceleration() { return PLAYER_ACCELERATION; }

static inline float get_player_radius() { return PLAYER_RADIUS; }

static inline int get_player_starting_money() { return PLAYER_STARTING_MONEY; }

static inline int get_player_max_health() { return PLAYER_MAX_HEALTH; }

class GameSetup {
public:
    static GameLoop setup(
        const std::vector<std::unique_ptr<ClientHandler>>& clients) {
        std::vector<std::unique_ptr<PlayerHandler>> handlers;
        std::vector<std::shared_ptr<Player>> players;
        auto map = get_map();
        for (auto& c : clients) {
            auto p = std::make_shared<Player>(
                get_player_id(), get_starting_position(),
                get_starting_equipment(), map, get_player_max_velocity(),
                get_player_acceleration(), get_player_radius(),
                get_player_starting_money(), get_player_max_health());

            /*
             * Map no puede tener un vector de referencias a los players, pues
             * eśtos están siendo movidos constantemente en distintos vectores a
             * lo largo del programa
             * */
            map->add_collidable(p);
            /*
             * Si muevo p acá ya perdí el ownership del puntero como para seguir
             * pasándolo
             * */
            auto h = c->play(p);
            h->start();
            handlers.push_back(std::move(h));
            players.push_back(std::move(p));  // <-- acá
        }

        return GameLoop(std::move(handlers), std::move(players), std::move(map),
                        get_tick_rate(), get_rounds(), get_round_time(),
                        get_time_out());
    }
};

#endif
