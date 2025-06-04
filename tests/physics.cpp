#include "gtest/gtest.h"
#include "server/model/player_physics.h"

#include "mock_player.h"

namespace {
TEST(PlayerPhysics, PlayerCanWalkFreelyIfThereAreNotAnyObstaclesInTheMap) {
    Map dummy_map;
    float player_radius = 1;
    float player_velocity = 1;
    float player_acceleration = 0;
    Position initial_pos = Position(0, 0);
    Direction dummy_dir(1, 0);

    PlayerPhysics p(initial_pos, dummy_dir, player_velocity, player_acceleration, player_radius,
                    dummy_map);

    Position expected = initial_pos;
    EXPECT_EQ(expected, p.get_position());

    Direction move_dir(1, 0);
    expected = Position(1, 0);
    p.move(move_dir);
    EXPECT_EQ(expected, p.get_position());

    move_dir = Direction(0, 1);
    expected = Position(1, 1);
    p.move(move_dir);
    EXPECT_EQ(expected, p.get_position());

    move_dir = Direction(1, 1);
    expected = Position(1 + 1 / std::sqrt(2), 1 + 1 / std::sqrt(2));
    p.move(move_dir);
    EXPECT_EQ(expected, p.get_position());

    move_dir = Direction(-1, 0);
    expected = Position(1 / std::sqrt(2), 1 + 1 / std::sqrt(2));
    p.move(move_dir);
    EXPECT_NEAR(expected.x, p.get_position().x, 1e-7);
    EXPECT_NEAR(expected.y, p.get_position().y, 1e-7);
}

TEST(PlayerPhysics, PlayerCanNotDirectlyWalkThroughAnotherPlayer) {
    Map map;
    float player_radius = 1;
    float player_velocity = 1;
    float player_acceleration = 0;
    Position initial_pos = Position(0, 0);
    Position p2_pos = Position(0, 2.5);
    Direction move_direction(0, 1);
    Direction dummy_dir(1, 0);

    Position expected(0, 0.5);

    auto p1 = std::make_unique<PlayerPhysics>(initial_pos, dummy_dir, player_velocity,
                                              player_acceleration, player_radius, map);
    auto p2 = std::make_unique<MockPlayer>(p2_pos);

    PlayerPhysics* p1_ptr = p1.get();

    map.add_collidable(std::move(p2));
    map.add_collidable(std::move(p1));

    p1_ptr->move(move_direction);
    EXPECT_EQ(p1_ptr->get_position(), expected);
}

TEST(PlayerPhysics, PlayerCanNotSideWalkThroughAnotherPlayer) {
    Map map;
    float player_radius = 1;
    float player_velocity = 1;
    float player_acceleration = 0;
    Position initial_pos = Position(0, 0);
    Position p2_pos = Position(0.5, 2.5);
    Direction move_direction(0, 1);
    Direction dummy_dir(1, 0);

    /*
     * Esperar que la posición del jugador luego del movimiento sea la resta de la
     * intersección con el obstáculo y el producto de la dirección de movimiento y
     * el radio del jugador
     * */
    Position intended_destination = initial_pos + move_direction * player_velocity;
    Position intersection = p2_pos + p2_pos.get_direction(intended_destination) * player_radius;
    Position expected = intersection - move_direction * player_radius;

    auto p1 = std::make_unique<PlayerPhysics>(initial_pos, dummy_dir, player_velocity,
                                              player_acceleration, player_radius, map);
    auto p2 = std::make_unique<MockPlayer>(p2_pos);

    PlayerPhysics* p1_ptr = p1.get();

    map.add_collidable(std::move(p2));
    map.add_collidable(std::move(p1));

    p1_ptr->move(move_direction);
    EXPECT_EQ(p1_ptr->get_position(), expected);
}

}  // namespace
