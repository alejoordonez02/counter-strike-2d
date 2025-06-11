#include "gtest/gtest.h"
#include "server/model/attack.h"
#include "server/model/weapon.h"
#include "tests/server/model/mocks/mock_player_physics.h"

class MagicWeapon: public Weapon {
    public:
    MagicWeapon(): Weapon(100, 100, 100, 100, 1, 0, 0) {}
};

class AttackActionTest: public ::testing::Test {
    protected:
    Map map;
    Position player_pos{0, 0};
    Position enemy_pos{10, 10};
    Position aligned_enemy_pos{20, 20};
    int player_health = 1;
    float player_shield = 1;
    bool player_alive = true;
    MagicWeapon weapon;

    std::unique_ptr<PlayerPhysics> player;
    std::unique_ptr<MockPlayerPhysics> enemy;
    std::unique_ptr<MockPlayerPhysics> aligned_enemy;
    PlayerPhysics* player_raw;
    MockPlayerPhysics* enemy_raw;
    MockPlayerPhysics* aligned_enemy_raw;

    void SetUp() override {
        player = std::make_unique<PlayerPhysics>(player_pos, player_health,
                                                 player_shield, player_alive, 1,
                                                 1, 1, map);
        enemy = std::make_unique<MockPlayerPhysics>(enemy_pos);

        aligned_enemy = std::make_unique<MockPlayerPhysics>(aligned_enemy_pos);

        player_raw = player.get();
        enemy_raw = enemy.get();
        aligned_enemy_raw = aligned_enemy.get();

        map.add_collidable(*player);
        map.add_collidable(*enemy);
        map.add_collidable(*aligned_enemy);

        weapon.update(1);
    }
};

TEST_F(AttackActionTest, AttackingWithGoodAimResultsInHitboxGettingAttacked) {
    Direction aim_dir = player_pos.get_direction(enemy_raw->get_position());
    Attack attack_action(*player_raw, player_pos, aim_dir, weapon, map);

    EXPECT_CALL(*enemy_raw, get_attacked(::testing::_));
    attack_action.update(1);
}

TEST_F(AttackActionTest,
       AttackingWithBadAimDoesNotResultInHitboxGettingAttacked) {
    Direction aim_dir = player_pos.get_direction(enemy_raw->get_position()) +
                        Direction(100, 0);
    Attack attack_action(*player_raw, player_pos, aim_dir, weapon, map);

    EXPECT_CALL(*enemy_raw, get_attacked(::testing::_)).Times(0);
    attack_action.update(1);
}

TEST_F(AttackActionTest,
       AttackingToAlignedHitboxedDoesNotResultInColateralDamage) {
    Direction aim_dir = player_pos.get_direction(enemy_raw->get_position());
    Attack attack_action(*player_raw, player_pos, aim_dir, weapon, map);

    EXPECT_CALL(*enemy_raw, get_attacked(::testing::_));
    EXPECT_CALL(*aligned_enemy_raw, get_attacked(::testing::_)).Times(0);
    attack_action.update(1);
}
