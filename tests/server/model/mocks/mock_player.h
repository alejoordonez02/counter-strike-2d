#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include <map>
#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "gmock/gmock.h"
#include "server/game/world/map.h"
#include "server/game/world/player.h"

class MockPlayer: public Player {
private:
    static inline int default_id = 0;
    static inline Position default_pos{0, 0};
    static inline float default_max_velocity = 3.0f;
    static inline float default_acceleration = 1.0f;
    static inline float default_radius = 1.0f;
    static inline int default_money = 500;
    static inline int default_max_health = 100;

    static inline std::shared_ptr<Map> get_default_map() {
        return std::make_shared<Map>(
            std::vector<std::shared_ptr<Hitbox>>{},
            std::vector<std::unique_ptr<Drop>>{}, std::vector<Structure>{},
            std::vector<Position>{}, std::vector<Position>{});
    }

    /* Weapon(WeaponName name, WeaponType type, float damage, float accuracy,
           float range, float bullet_size, float fire_rate, float reload_time,
           int ammo_capacity, int starting_ammo, int cost, int ammo_cost); */
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
    /* Player(int id, Position pos, std::shared_ptr<Weapon> primary,
           std::shared_ptr<Weapon> secondary, std::shared_ptr<Weapon> knife,
           std::weak_ptr<Map> map, float max_velocity, float acceleration,
           float radius, int money, int health,
           std::shared_ptr<WeaponFactory> weapon_factory); */
    MockPlayer(Position& pos, std::weak_ptr<Map> map):
        Player(default_id, pos, nullptr, get_default_secondary(), get_knife(),
               map, default_max_velocity, default_acceleration, default_radius,
               default_money, default_max_health,
               std::make_shared<WeaponFactory>(
                   std::map<WeaponName, WeaponConfig>{})) {}

    MockPlayer():
        Player(default_id, default_pos, nullptr, get_default_secondary(),
               get_knife(), get_default_map(), default_max_velocity,
               default_acceleration, default_radius, default_money,
               default_max_health,
               std::make_shared<WeaponFactory>(
                   std::map<WeaponName, WeaponConfig>{})) {}

    MOCK_METHOD(void, switch_side, (), (override));
    MOCK_METHOD(void, start_moving, (Direction dir), (override));
    MOCK_METHOD(void, start_attacking, (), (override));
    MOCK_METHOD(void, get_attacked, (int damage), (override));
    MOCK_METHOD(void, use_primary, (), ());
    MOCK_METHOD(void, use_secondary, (), ());
    MOCK_METHOD(void, use_knife, (), ());
    MOCK_METHOD(void, buy_primary, (Weapon & weapon), ());
    MOCK_METHOD(void, buy_secondary, (Weapon & weapon), ());
    MOCK_METHOD(void, buy_primary_ammo, (const int& count), ());
    MOCK_METHOD(void, buy_secondary_ammo, (const int& count), ());
    MOCK_METHOD(void, teleport_to_spawn, (), (override));
    MOCK_METHOD(void, start_planting, (), (override));
    MOCK_METHOD(void, start_defusing, (), (override));
    MOCK_METHOD(void, give_bomb, (), (override));
    MOCK_METHOD(void, restart, (), (override));
    MOCK_METHOD(void, drop_bomb, (), (override));

    virtual ~MockPlayer() = default;
};

#endif
