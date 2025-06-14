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
    MagicWeapon weapon;
    std::shared_ptr<Map> map;
    std::weak_ptr<Map> map_weak_ptr;

    float player_max_vel = 1.0f;
    float player_accel = 1.0f;
    float player_radius = 1.0f;

    Position player_pos{0, 0};
    Position enemy_pos{10, 0};
    Position aligned_enemy_pos{20, 0};

    std::shared_ptr<MockPlayer> enemy;
    std::shared_ptr<MockPlayer> aligned_enemy;

    std::unique_ptr<PlayerPhysics> attacker_physics;

    void SetUp() override {
        map = std::make_shared<Map>();
        map_weak_ptr = map;

        attacker_physics = std::make_unique<PlayerPhysics>(
                player_pos, player_max_vel, player_accel, player_radius,
                map_weak_ptr);

        enemy = std::make_shared<MockPlayer>(enemy_pos, map);
        aligned_enemy =
                std::make_shared<MockPlayer>(aligned_enemy_pos, map_weak_ptr);

        map->add_collidable(enemy);
        map->add_collidable(aligned_enemy);

        weapon.update(1);
    }
};

TEST_F(AttackActionTest, AttackingWithGoodAimResultsInHitboxGettingAttacked) {
    Direction aim_dir = player_pos.get_direction(enemy->get_position());
    Attack attack_action(*attacker_physics, player_pos, aim_dir, weapon,
                         map_weak_ptr);
    EXPECT_CALL(*enemy, get_attacked(::testing::_));
    attack_action.update(1);
}

TEST_F(AttackActionTest,
       AttackingWithBadAimDoesNotResultInHitboxGettingAttacked) {
    Direction bad_aim_dir =
            player_pos.get_direction(enemy->get_position()) + Direction(0, 100);
    Attack attack_action(*attacker_physics, player_pos, bad_aim_dir, weapon,
                         map_weak_ptr);
    EXPECT_CALL(*enemy, get_attacked(::testing::_)).Times(0);
    attack_action.update(1);
}

TEST_F(AttackActionTest,
       AttackingToAlignedHitboxedDoesNotResultInColateralDamage) {
    Direction aim_dir = player_pos.get_direction(enemy->get_position());
    Attack attack_action(*attacker_physics, player_pos, aim_dir, weapon,
                         map_weak_ptr);
    EXPECT_CALL(*enemy, get_attacked(::testing::_));
    EXPECT_CALL(*aligned_enemy, get_attacked(::testing::_)).Times(0);
    attack_action.update(1);
}
