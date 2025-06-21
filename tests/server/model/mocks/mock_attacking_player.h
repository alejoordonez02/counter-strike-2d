#ifndef MOCK_ATTACKING_PLAYER_H
#define MOCK_ATTACKING_PLAYER_H

#include <gmock/gmock.h>

#include <memory>

#include "server/world/equipment/equipment.h"
#include "server/world/equipment/weapons.h"
#include "server/world/map.h"
#include "server/world/player.h"

class MockAttackingPlayer: public Player {
    static inline int default_id = 0;
    static inline float default_max_velocity = 1.0f;
    static inline float default_acceleration = 1000;
    static inline float default_radius = 1.0f;
    static inline int default_money = 500;
    static inline int default_max_health = 100;

    static inline Equipment get_default_equipment() {
        return Equipment(Fist(), Glock(), 0);
    }

public:
    MockAttackingPlayer(Position& pos, std::weak_ptr<Map> map,
                        float radius = default_radius):
        Player(default_id, pos, get_default_equipment(), map,
               default_max_velocity, default_acceleration, radius,
               default_money, default_max_health) {}
    MOCK_METHOD(void, get_attacked, (int damage), (override));
    void teleport_to_spawn() override {}
};

#endif
