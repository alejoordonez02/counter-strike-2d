#include <cmath>
#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "gtest/gtest.h"
#include "server/game/world/map.h"
#include "tests/server/model/mocks/mock_moving_player.h"

class CollisionsTest: public ::testing::Test {
protected:
    std::shared_ptr<Map> map;

    std::shared_ptr<MovingPlayer> get_player(Position& pos_ref,
                                             float radius = 1) {
        return std::make_shared<MovingPlayer>(pos_ref, map, radius);
    }

    void EXPECT_POS_EQ(const Position& pos, const Position& other) const {
        EXPECT_NEAR(pos.x, other.x, 1e-7);
        EXPECT_NEAR(pos.y, other.y, 1e-7);
    }

    void SetUp() override {
        map = std::make_shared<Map>(
            std::vector<std::shared_ptr<Hitbox>>{}, std::vector<Structure>{},
            std::vector<Position>{}, std::vector<Position>{});
    }
};

TEST_F(CollisionsTest, PlayerCanWalkFreelyIfThereAreNotAnyObstacles) {
    Position initial_pos(0, 0);
    auto player = get_player(initial_pos);

    player->start_moving(Direction(1, 0));
    player->update(1);
    EXPECT_POS_EQ(player->get_position(), Position(1, 0));

    player->start_moving(Direction(1, 1));
    player->update(1);
    EXPECT_POS_EQ(player->get_position(),
                  Position(1 + 1 / std::sqrt(2), 1 / std::sqrt(2)));

    player->start_moving(Direction(0, 1));
    player->update(1);
    EXPECT_POS_EQ(player->get_position(),
                  Position(1 + 1 / std::sqrt(2), 1 + 1 / std::sqrt(2)));

    player->start_moving(Direction(-1, -1));
    player->update(1);
    EXPECT_POS_EQ(player->get_position(), Position(1, 1));
}

TEST_F(CollisionsTest, PlayerCannotWalkThroughAnotherPlayer) {
    Position p1_pos(0, 0);
    Position p2_pos(0, 2.5f);
    float player_radius = 1;

    auto p1 = get_player(p1_pos, player_radius);
    auto p2 = get_player(p2_pos, player_radius);

    map->add_collidable(p2);
    map->add_collidable(p1);

    p1->start_moving(Direction(0, 1));
    p1->update(1);

    EXPECT_POS_EQ(p1->get_position(), Position(0, 0.5f));
}
