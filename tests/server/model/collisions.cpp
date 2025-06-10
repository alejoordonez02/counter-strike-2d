#include <cmath>
#include <memory>

#include "gtest/gtest.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"

class CollisionsTest: public ::testing::Test {
    protected:
    float player_radius = 1.0f;
    float player_max_velocity = 1.0f;
    float player_acceleration = 100.0f;  // trigger max velocity
    int dummy_health = 100;
    float dummy_shield = 0.0f;
    bool dummy_alive = true;
    Map map;

    std::unique_ptr<PlayerPhysics> make_player(Position& pos) {
        return std::make_unique<PlayerPhysics>(
                pos, dummy_health, dummy_shield, dummy_alive,
                player_max_velocity, player_acceleration, player_radius, map);
    }

    void EXPECT_POS_EQ(const Position& pos, const Position& other) const {
        EXPECT_FLOAT_EQ(pos.x, other.x);
        EXPECT_FLOAT_EQ(pos.y, other.y);
    }
};

TEST_F(CollisionsTest, PlayerCanWalkFreelyIfTheraAreNotAnyObstacles) {
    Position initial_pos(0, 0);
    auto player = make_player(initial_pos);

    EXPECT_POS_EQ(initial_pos, player->get_position());

    player->start_moving(Direction(1, 0));
    player->update(1);
    EXPECT_POS_EQ(Position(1, 0), player->get_position());

    player->start_moving(Direction(0, 1));
    player->update(1);
    EXPECT_POS_EQ(Position(1, 1), player->get_position());

    player->start_moving(Direction(1, 1));
    player->update(1);
    float diag = 1 / std::sqrt(2);
    EXPECT_NEAR(1 + diag, player->get_position().x, 1e-7);
    EXPECT_NEAR(1 + diag, player->get_position().y, 1e-7);

    player->start_moving(Direction(-1, 0));
    player->update(1);
    EXPECT_NEAR(diag, player->get_position().x, 1e-7);
    EXPECT_NEAR(1 + diag, player->get_position().y, 1e-7);
}

TEST_F(CollisionsTest, PlayerCannotWalkThroughAnotherPlayer) {
    Position p1_pos(0, 0);
    Position p2_pos(0, 2.5);

    auto p1 = make_player(p1_pos);
    auto p2 = make_player(p2_pos);

    map.add_collidable(*p2);
    map.add_collidable(*p1);

    p1->start_moving(Direction(0, 1));
    p1->update(1);

    EXPECT_POS_EQ(Position(0, 0.5), p1->get_position());
}

TEST_F(CollisionsTest, PlayerCannotSideWalkThroughAnotherPlayer) {
    Position p1_pos(0, 0);
    Position p2_pos(0, 2.5);

    auto p1 = make_player(p1_pos);
    auto p2 = make_player(p2_pos);

    map.add_collidable(*p2);
    map.add_collidable(*p1);

    Direction move_dir(0, 1);

    Position intended_destination = p1_pos + move_dir * player_max_velocity;
    Position intersection =
            p2_pos + p2_pos.get_direction(intended_destination) * player_radius;
    Position expected = intersection - move_dir * player_radius;

    p1->start_moving(move_dir);
    p1->update(1);

    EXPECT_POS_EQ(expected, p1->get_position());
}
