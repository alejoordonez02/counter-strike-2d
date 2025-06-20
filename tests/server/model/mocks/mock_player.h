#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "gmock/gmock.h"
#include "server/world/equipment/equipment.h"
#include "server/world/equipment/weapon.h"
#include "server/world/equipment/weapons.h"
#include "server/world/map.h"
#include "server/world/player.h"

class MockPlayer: public Player {
private:
    static inline int default_id = 0;
    static inline Position default_pos_val{0, 0};
    static inline float default_max_velocity = 3.0f;
    static inline float default_acceleration = 1.0f;
    static inline float default_radius = 1.0f;
    static inline int default_money = 500;
    static inline int default_max_health = 100;

    static inline std::shared_ptr<Map> get_default_map() {
        return std::make_shared<Map>();
    }

    static inline std::unique_ptr<Equipment> get_default_equipment() {
        return std::make_unique<Equipment>(std::make_unique<Fist>(),
                                           std::make_unique<Glock>(),
                                           std::make_unique<Knife>(), 0);
    }

public:
    MockPlayer(Position& pos, std::weak_ptr<Map> map):
        Player(default_id, pos, get_default_equipment(), map,
               default_max_velocity, default_acceleration, default_radius,
               default_money, default_max_health) {}

    MockPlayer():
        Player(default_id, default_pos_val, get_default_equipment(),
               get_default_map(), default_max_velocity, default_acceleration,
               default_radius, default_money, default_max_health) {}

    MOCK_METHOD(void, start_moving, (Direction dir), (override));
    MOCK_METHOD(void, start_attacking, (), (override));
    MOCK_METHOD(void, get_attacked, (int damage), (override));
    /* MOCK_METHOD(std::optional<Position>, intersect, (const Trajectory& t),
                (const)); */
    MOCK_METHOD(void, use_primary, (), ());
    MOCK_METHOD(void, use_secondary, (), ());
    MOCK_METHOD(void, use_knife, (), ());
    MOCK_METHOD(void, buy_primary, (Weapon & weapon), ());
    MOCK_METHOD(void, buy_secondary, (Weapon & weapon), ());
    MOCK_METHOD(void, buy_primary_ammo, (const int& count), ());
    MOCK_METHOD(void, buy_secondary_ammo, (const int& count), ());
    MOCK_METHOD(void, teleport_to_spawn, (), (override));

    virtual ~MockPlayer() = default;
};

#endif
