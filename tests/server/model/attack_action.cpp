#include "common/direction.h"
#include "common/position.h"
#include "gtest/gtest.h"
#include "server/game/world/map.h"
#include "tests/server/model/mocks/mock_attacking_player.h"

class MagicWeapon: public Weapon {
public:
    MagicWeapon():
        Weapon(WeaponName::NONE, WeaponType::NONE, 100, 100, 1000, 0, 1, 0, 100,
               100, 0, 0) {}
};

class PlayerAttackTest: public ::testing::Test {
protected:
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::vector<Structure> bomb_site;
    std::vector<Position> tt_spawn;
    std::vector<Position> ct_spawn;
    std::shared_ptr<Map> map;
    std::weak_ptr<Map> map_weak_ptr;

    Position player_pos{0, 0};
    Position enemy_pos{10, 0};
    Position aligned_enemy_pos{20, 0};

    std::shared_ptr<MockAttackingPlayer> player;
    std::shared_ptr<MockAttackingPlayer> enemy;
    std::shared_ptr<MockAttackingPlayer> aligned_enemy;

    void SetUp() override {
        map = std::make_shared<Map>(
            std::vector<std::shared_ptr<Hitbox>>{}, std::vector<Drop>{},
            std::vector<Structure>{}, std::vector<Position>{},
            std::vector<Position>{});
        map_weak_ptr = map;

        player =
            std::make_shared<MockAttackingPlayer>(player_pos, map_weak_ptr);
        enemy = std::make_shared<MockAttackingPlayer>(enemy_pos, map_weak_ptr);
        aligned_enemy = std::make_shared<MockAttackingPlayer>(aligned_enemy_pos,
                                                              map_weak_ptr);

        map->add_collidable(player);
        map->add_collidable(enemy);
        map->add_collidable(aligned_enemy);

        MagicWeapon weapon;
        player->set_weapon(std::make_shared<Weapon>(weapon));
    }
};

TEST_F(PlayerAttackTest, AttackingWithGoodAimResultsInHitboxGettingAttacked) {
    Direction aim_dir = player_pos.get_direction(enemy->get_position());
    player->aim(aim_dir);

    EXPECT_CALL(*enemy, get_attacked(::testing::_));
    player->start_attacking();
    player->update(1);
}

TEST_F(PlayerAttackTest,
       AttackingWithBadAimDoesNotResultInHitboxGettingAttacked) {
    Direction bad_aim_dir =
        player_pos.get_direction(enemy->get_position()) + Direction(0, 100);
    player->aim(bad_aim_dir);

    EXPECT_CALL(*enemy, get_attacked(::testing::_)).Times(0);
    player->start_attacking();
    player->update(1);
}

TEST_F(PlayerAttackTest,
       AttackingToAlignedHitboxedDoesNotResultInColateralDamage) {
    Direction aim_dir = player_pos.get_direction(enemy->get_position());
    player->aim(aim_dir);

    EXPECT_CALL(*enemy, get_attacked(::testing::_));
    EXPECT_CALL(*aligned_enemy, get_attacked(::testing::_)).Times(0);
    player->start_attacking();
    player->update(1);
}
