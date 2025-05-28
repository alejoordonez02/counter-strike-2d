#include "../common/player_commands/attack.h"
#include "../common/player_commands/move.h"
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
    auto mock = std::make_unique<MockPlayer>(Position(5, 5));
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
    auto mock = std::make_unique<MockPlayer>(Position(20, 30));
    MockPlayer* mock_ptr = mock.get();
    map.add_collidable(std::move(mock));
    Attack attack(Position(1, 1));
    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_)).Times(0);
    attack.execute(p);
}

namespace {
TEST(PlayerTest, PlayerMoveNorthFromX0Y0WithVelocity1) {
    Map map;
    Player p(Position(0, 0), map);
    Direction dir(0, 1);
    Move move(dir);
    move.execute(p);
    EXPECT_EQ(p.get_position(), Position(0, 1));
}

TEST(PlayerTest, PlayerCanNotWalkThroughAnObstacle) {
    Map map;
    Player p(Position(0, 0), map);
    Direction dir(0, 1);
    Move move(dir);
    move.execute(p);
    EXPECT_EQ(p.get_position(), Position(0, 1));
}
}  // namespace

}  // namespace
