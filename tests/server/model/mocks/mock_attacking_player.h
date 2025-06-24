#ifndef MOCK_ATTACKING_PLAYER_H
#define MOCK_ATTACKING_PLAYER_H

#include <gmock/gmock.h>

#include <memory>

#include "server/game/world/map.h"
#include "server/game/world/player.h"

class MockAttackingPlayer: public Player {
    static inline int default_id = 0;
    static inline float default_max_velocity = 1.0f;
    static inline float default_acceleration = 1000;
    static inline float default_radius = 1.0f;
    static inline int default_money = 500;
    static inline int default_max_health = 100;

    static inline std::shared_ptr<Weapon> get_default_secondary() {
        return std::make_shared<Weapon>(WeaponName::GLOCK,
                                        WeaponType::SECONDARY, 20, 1, 300, 0, 4,
                                        3, 25, 50, 100, 1);
    }

    static inline std::shared_ptr<Weapon> get_knife() {
        return std::make_shared<Weapon>(WeaponName::KNIFE, WeaponType::KNIFE,
                                        20, 1, 10, 1, 3, 0, 100, 100, 0, 0);
    }

public:
    MockAttackingPlayer(Position& pos, std::weak_ptr<Map> map,
                        float radius = default_radius):
        Player(default_id, pos, nullptr, get_default_secondary(), get_knife(),
               map, default_max_velocity, default_acceleration, radius,
               default_money, default_max_health,
               std::make_shared<WeaponFactory>(
                   std::map<WeaponName, WeaponConfig>{})) {}

    MOCK_METHOD(void, teleport_to_spawn, (), (override));
    MOCK_METHOD(void, get_attacked, (int damage), (override));
    MOCK_METHOD(void, switch_side, (), (override));
    MOCK_METHOD(void, start_planting, (), (override));
    MOCK_METHOD(void, start_defusing, (), (override));
    MOCK_METHOD(void, give_bomb, (), (override));
    MOCK_METHOD(void, restart, (), (override));
    MOCK_METHOD(void, drop_bomb, (), (override));
};

#endif
