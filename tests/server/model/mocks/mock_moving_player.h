#ifndef MOVING_PLAYER_H
#define MOVING_PLAYER_H

#include <memory>

#include "server/model/equipment.h"
#include "server/model/map.h"
#include "server/model/player.h"
#include "server/model/weapons.h"

class MovingPlayer: public Player {
    static inline int default_id = 0;
    static inline float default_max_velocity = 1.0f;
    static inline float default_acceleration = 1000;  // trigger max vel
    static inline float default_radius = 1.0f;
    static inline int default_money = 500;
    static inline int default_max_health = 100;

    static inline std::unique_ptr<Equipment> get_default_equipment() {
        return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                           std::make_unique<Glock>(),
                                           std::make_unique<Knife>(), 0);
    }

public:
    MovingPlayer(Position& pos, std::weak_ptr<Map> map,
                 float radius = default_radius):
            Player(default_id, pos, get_default_equipment(), map,
                   default_max_velocity, default_acceleration, radius,
                   default_money, default_max_health) {}

    void teleport_to_spawn() override {}
};

#endif
