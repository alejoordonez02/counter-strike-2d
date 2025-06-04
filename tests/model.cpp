#include "../server/player_commands/attack.h"
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

    Player p(Position(0, 0), Direction(1, 0), FullEquipment(), map);
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

    Player p(Position(0, 0), Direction(1, 0), FullEquipment(), map);
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

    Player p(Position(0, 0), Direction(1, 0), FullEquipment(), map);
    p.use_primary();

    Attack attack(Position(10, 1));

    EXPECT_CALL(*mock_ptr, get_attacked(::testing::_)).Times(0);
    attack.execute(p);
}
}  // namespace
