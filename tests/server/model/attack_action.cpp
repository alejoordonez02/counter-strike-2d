#include "common/direction.h"
#include "common/position.h"
#include "gtest/gtest.h"
#include "server/model/attack.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"
#include "server/model/weapon.h"
#include "tests/server/model/mocks/mock_player.h"

class MagicWeapon: public Weapon {
public:
    MagicWeapon(): Weapon(100, 100, 100, 100, 1, 0, 0) {}
};

class AttackActionTest: public ::testing::Test {
protected:
    Map map;
    Position player_actual_pos_obj{0, 0};
    Position enemy_actual_pos_obj{10, 0};

    Position aligned_enemy_actual_pos_obj{20, 0};

    float player_max_vel = 1.0f;
    float player_accel = 1.0f;
    float player_radius = 1.0f;

    MagicWeapon weapon;

    std::unique_ptr<PlayerPhysics> attacker_physics;

    std::unique_ptr<MockPlayer> enemy;
    std::unique_ptr<MockPlayer> aligned_enemy;

    PlayerPhysics* attacker_physics_raw;
    MockPlayer* enemy_raw;
    MockPlayer* aligned_enemy_raw;

    void SetUp() override {
        attacker_physics = std::make_unique<PlayerPhysics>(
                player_actual_pos_obj, player_max_vel, player_accel,
                player_radius, map);
        attacker_physics_raw = attacker_physics.get();

        enemy = std::make_unique<MockPlayer>(enemy_actual_pos_obj, map);
        aligned_enemy =
                std::make_unique<MockPlayer>(aligned_enemy_actual_pos_obj, map);

        enemy_raw = enemy.get();
        aligned_enemy_raw = aligned_enemy.get();

        map.add_collidable(*enemy_raw);
        map.add_collidable(*aligned_enemy_raw);

        weapon.update(1);
    }
};

TEST_F(AttackActionTest, AttackingWithGoodAimResultsInHitboxGettingAttacked) {
    Direction aim_dir =
            player_actual_pos_obj.get_direction(enemy_raw->get_position());
    Attack attack_action(*attacker_physics_raw, player_actual_pos_obj, aim_dir,
                         weapon, map);

    EXPECT_CALL(*enemy_raw, get_attacked(::testing::_));
    attack_action.update(1);
}

TEST_F(AttackActionTest,
       AttackingWithBadAimDoesNotResultInHitboxGettingAttacked) {
    Direction bad_aim_dir =
            player_actual_pos_obj.get_direction(enemy_raw->get_position()) +
            Direction(0, 100);
    Attack attack_action(*attacker_physics_raw, player_actual_pos_obj,
                         bad_aim_dir, weapon, map);

    EXPECT_CALL(*enemy_raw, get_attacked(::testing::_)).Times(0);
    attack_action.update(1);
}

TEST_F(AttackActionTest,
       AttackingToAlignedHitboxedDoesNotResultInColateralDamage) {
    Direction aim_dir =
            player_actual_pos_obj.get_direction(enemy_raw->get_position());
    Attack attack_action(*attacker_physics_raw, player_actual_pos_obj, aim_dir,
                         weapon, map);

    EXPECT_CALL(*enemy_raw, get_attacked(::testing::_));

    EXPECT_CALL(*aligned_enemy_raw, get_attacked(::testing::_)).Times(0);
    attack_action.update(1);
}
