#include "../server/player_commands/attack.h"
#include "../server/player_commands/move.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "equipment.h"
#include "mock_player.h"
#include "random.h"
#include "weapons.h"

struct RandomInitializer {
    RandomInitializer() {
        Random::set_custom_generator([]() { return 0.0f; });
    }
};

static RandomInitializer randomInitializer;

struct FullEquipment: public Equipment {
    FullEquipment():
            Equipment(std::make_unique<Awp>(), std::make_unique<Glock>(), std::make_unique<Knife>(),
                      100) {}
};

namespace {
TEST(ModelTest, PlayerGetsAttackedWhenShoot) {
    Map map;
    auto mock = std::make_unique<MockPlayer>(Position(5, 5));
    MockPlayer* mock_ptr = mock.get();
    map.add_collidable(std::move(mock));

    Player p(Position(0, 0), FullEquipment(), map);
    p.use_primary();

    Attack attack(Position(1, 1));

    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_));
    attack.execute(p);
}

TEST(ModelTest, PlayerDoesNotGetAttackedWhenShootIfCovered) {
    Map map;
    auto mock = std::make_unique<MockPlayer>(Position(5, 5));
    auto obstacle = std::make_unique<MockPlayer>(Position(3, 3));

    MockPlayer* mock_ptr = mock.get();
    MockPlayer* obstacle_ptr = obstacle.get();

    map.add_collidable(std::move(mock));
    map.add_collidable(std::move(obstacle));

    Player p(Position(0, 0), FullEquipment(), map);
    p.use_primary();

    Attack attack(Position(1, 1));

    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_)).Times(0);
    EXPECT_CALL(*obstacle_ptr, get_attacked(::testing::_));
    attack.execute(p);
}

TEST(ModelTest, PlayerDoesNotGetAttackedWhenAttackerMissesShoot) {
    Map map;
    auto mock = std::make_unique<MockPlayer>(Position(5, 5));
    MockPlayer* mock_ptr = mock.get();
    map.add_collidable(std::move(mock));

    Player p(Position(0, 0), FullEquipment(), map);
    p.use_primary();

    Attack attack(Position(10, 1));

    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_)).Times(0);
    attack.execute(p);
}
}  // namespace

namespace {
TEST(PlayerTest, PlayerMoveNorthFromX0Y0WithVelocity1) {
    Map map;
    Player p(Position(0, 0), FullEquipment(), map);
    Direction dir(0, 1);
    Move move(dir);
    move.execute(p);
    EXPECT_EQ(p.get_position(), Position(0, 1));
}

TEST(PlayerTest, PlayerCanNotWalkThroughAnObstacle) {
    Map map;
    Player p(Position(0, 0), FullEquipment(), map);
    auto mock = std::make_unique<MockPlayer>(Position(0, 0.5));
    map.add_collidable(std::move(mock));
    Direction dir(0, 1);
    Move move(dir);
    move.execute(p);
    EXPECT_EQ(p.get_position(), Position(0, 0.5));
}
}  // namespace
