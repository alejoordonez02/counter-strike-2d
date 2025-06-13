#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "server/client_handler.h"
#include "server/game_loop.h"
#include "server/model/equipment.h"
#include "server/model/map.h"
#include "server/model/player.h"
#include "server/model/weapons.h"
#include "server/player_handler.h"

#define TICK_RATE 64
#define ROUNDS 15
#define ROUND_TIME 600
#define TIME_OUT 10
#define PLAYER_MAX_VELOCITY 5.0f
#define PLAYER_ACCELERATION 10.0f
#define PLAYER_RADIUS 0.5f
#define PLAYER_STARTING_MONEY 800
#define PLAYER_MAX_HEALTH 100

/*
 * GameSetup usa el parser para leer la config e instanciar el juego. Estos get
 * vendrían a ser los retornos del parser
 * */
static inline Map get_map() {
    Map map;
    return map;
}

static inline Position get_starting_position() { return Position(0, 0); }

static inline std::unique_ptr<Equipment> get_starting_equipment() {
    return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                       std::make_unique<Glock>(),
                                       std::make_unique<Knife>(), 0);
};

static inline int get_tick_rate() { return TICK_RATE; }

static inline float get_rounds() { return ROUNDS; }

static inline float get_round_time() { return ROUND_TIME; }

static inline float get_time_out() { return TIME_OUT; }

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
        Map map = get_map();
        for (auto& c : clients) {
            auto p = std::make_shared<Player>(
                    get_starting_position(), get_starting_equipment(), map,
                    get_player_max_velocity(), get_player_acceleration(),
                    get_player_radius(), get_player_starting_money(),
                    get_player_max_health());

            map.add_collidable(*p);
            handlers.push_back(c->play(p));
            players.push_back(p);
        }

        return GameLoop(std::move(handlers), std::move(players), std::move(map),
                        get_tick_rate(), get_rounds(), get_round_time(),
                        get_time_out());
    }
};

#endif
