#include "server/model/attack.h"

#include "gtest/gtest.h"
#include "server/model/weapon.h"
#include "tests/mock_player_physics.h"

class MagicWeapon: public Weapon {
    public:
    MagicWeapon(): Weapon(100, 100, 1, 100, 0, 0) {}
};

namespace {
TEST(AttackActionStrategy, AttackingWithGoodAimResultsInHitboxGettingAttacked) {
    Map map;
    Position pos(0, 0);
    int dummy_health = 1;
    float dummy_shield = 1;
    bool dummy_alive = 1;

    auto p_ptr = std::make_unique<PlayerPhysics>(
            pos, dummy_health, dummy_shield, dummy_alive, 1, 1, 1, map);
    Position enemy_pos(Position(5, 5));
    auto enemy = std::make_unique<MockPlayerPhysics>(enemy_pos);
    auto p_raw = p_ptr.get();
    auto enemy_ptr = enemy.get();
    map.add_collidable(*p_ptr);
    map.add_collidable(*enemy);

    Direction aim_dir = pos.get_direction(enemy_pos);
    MagicWeapon weapon;
    Attack attack_action(*p_raw, pos, aim_dir, weapon, map);

    EXPECT_CALL(*enemy_ptr, get_attacked(100));
    attack_action.update(1);
}

TEST(AttackActionStrategy,  // cppcheck-suppress syntaxError
     AttackingWithBadAimDoesNotResultsInHitboxGettingAttacked) {
    Map map;
    Position pos(0, 0);
    int dummy_health = 1;
    float dummy_shield = 1;
    bool dummy_alive = 1;

    auto p_ptr = std::make_unique<PlayerPhysics>(
            pos, dummy_health, dummy_shield, dummy_alive, 1, 1, 1, map);
    Position enemy_pos(Position(5, 5));
    auto enemy = std::make_unique<MockPlayerPhysics>(enemy_pos);
    auto p_raw = p_ptr.get();
    auto enemy_ptr = enemy.get();
    map.add_collidable(*p_ptr);
    map.add_collidable(*enemy);

    Direction aim_dir = pos.get_direction(enemy_pos) + Direction(100, 0);
    MagicWeapon weapon;
    Attack attack_action(*p_raw, pos, aim_dir, weapon, map);

    EXPECT_CALL(*enemy_ptr, get_attacked(100)).Times(0);
    attack_action.update(1);
}
}  // namespace
