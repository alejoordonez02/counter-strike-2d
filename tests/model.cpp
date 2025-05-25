#include "../common/player_commands/attack.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "mock_player.h"

namespace {
/*
 * Ajustar este test para la accuracy de Weapon (existe la probabilidad de errar)
 * */
TEST(ModelTest, PlayerGetsAttackedWhenShoot) {
    Map map;
    Player p(Position(0, 0), map);
    auto mock = std::make_unique<MockPlayer>(Position(1, 1));
    MockPlayer* mock_ptr = mock.get();
    map.add_collidable(std::move(mock));
    Attack attack(Position(1, 1));
    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_));
    attack.execute(p);
}

TEST(ModelTest, PlayerDoesNotGetAttackedWhenShootIfCovered) {
    Map map;
    Player p(Position(0, 0), map);
    auto obstacle = std::make_unique<MockPlayer>(Position(1, 1));
    auto mock = std::make_unique<MockPlayer>(Position(2, 2));
    MockPlayer* obstacle_ptr = obstacle.get();
    MockPlayer* mock_ptr = mock.get();
    map.add_collidable(std::move(obstacle));
    map.add_collidable(std::move(mock));
    Attack attack(Position(1, 1));
    EXPECT_CALL(*obstacle_ptr, get_attacked(::testing::_));
    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_)).Times(0);
    attack.execute(p);
}

TEST(ModelTest, PlayerDoesNotGetAttackedWhenAttackerMissesShoot) {
    Map map;
    Player p(Position(0, 0), map);
    auto mock = std::make_unique<MockPlayer>(Position(2, 3));
    MockPlayer* mock_ptr = mock.get();
    map.add_collidable(std::move(mock));
    Attack attack(Position(1, 1));
    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_)).Times(0);
    attack.execute(p);
}

}  // namespace
