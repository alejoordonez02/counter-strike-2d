#include "gtest/gtest.h"
#define private public   /* ésto sólo en tests para no tener que agregar */
#define protected public /* getters innecesarios en el modelo */
#include "server/model/player_physics.h"
#undef private
#undef public

namespace {
TEST(PlayerPhysics, PlayerCanWalkFreelyIfThereAreNotAnyObstaclesInTheMap) {
    float player_radius = 1;
    float player_max_velocity = 1;
    float player_acceleration = 100;  // triggerear velocidad máxima
    Position initial_pos(0, 0);

    Map dummy_map;
    int dummy_health = 100;
    float dummy_shield = 0.0f;
    bool dummy_alive = true;

    PlayerPhysics p(initial_pos, dummy_health, dummy_shield, dummy_alive, player_max_velocity,
                    player_acceleration, player_radius, dummy_map);

    Position expected = initial_pos;
    EXPECT_EQ(expected, p.pos);

    Direction move_dir(1, 0);
    float dt = 1;
    expected = Position(1, 0);
    p.start_moving(move_dir);
    p.update(dt);
    EXPECT_EQ(expected, p.pos);

    move_dir = Direction(0, 1);
    expected = Position(1, 1);
    p.start_moving(move_dir);
    p.update(1);
    EXPECT_EQ(expected, p.pos);

    move_dir = Direction(1, 1);
    expected = Position(1 + 1 / std::sqrt(2), 1 + 1 / std::sqrt(2));
    p.start_moving(move_dir);
    p.update(1);
    EXPECT_EQ(expected, p.pos);

    move_dir = Direction(-1, 0);
    expected = Position(1 / std::sqrt(2), 1 + 1 / std::sqrt(2));
    p.start_moving(move_dir);
    p.update(1);
    EXPECT_NEAR(expected.x, p.pos.x, 1e-7);
    EXPECT_NEAR(expected.y, p.pos.y, 1e-7);
}

TEST(PlayerPhysics, PlayerCanNotDirectlyWalkThroughAnotherPlayer) {
    float player_radius = 1;
    float player_max_velocity = 1;
    float player_acceleration = 100;  // triggerear velocidad máxima
    Position initial_pos(0, 0);

    int dummy_health = 100;
    float dummy_shield = 0.0f;
    bool dummy_alive = true;

    Map map;

    auto p1 = std::make_unique<PlayerPhysics>(initial_pos, dummy_health, dummy_shield, dummy_alive,
                                              player_max_velocity, player_acceleration,
                                              player_radius, map);

    Position p2_pos = Position(0, 2.5);

    auto p2 = std::make_unique<PlayerPhysics>(p2_pos, dummy_health, dummy_shield, dummy_alive,
                                              player_max_velocity, player_acceleration,
                                              player_radius, map);

    PlayerPhysics* p1_ptr = p1.get();

    map.add_collidable(*p2);
    map.add_collidable(*p1);

    Position expected(0, 0.5);
    Direction move_dir(0, 1);

    p1_ptr->start_moving(move_dir);
    p1_ptr->update(1);
    EXPECT_EQ(p1_ptr->pos, expected);
}

TEST(PlayerPhysics, PlayerCanNotSideWalkThroughAnotherPlayer) {
    float player_radius = 1;
    float player_max_velocity = 1;
    float player_acceleration = 100;  // triggerear velocidad máxima
    Position initial_pos(0, 0);

    int dummy_health = 100;
    float dummy_shield = 0.0f;
    bool dummy_alive = true;

    Map map;

    auto p1 = std::make_unique<PlayerPhysics>(initial_pos, dummy_health, dummy_shield, dummy_alive,
                                              player_max_velocity, player_acceleration,
                                              player_radius, map);

    Position p2_pos = Position(0, 2.5);

    auto p2 = std::make_unique<PlayerPhysics>(p2_pos, dummy_health, dummy_shield, dummy_alive,
                                              player_max_velocity, player_acceleration,
                                              player_radius, map);

    PlayerPhysics* p1_ptr = p1.get();

    map.add_collidable(*p2);
    map.add_collidable(*p1);

    Direction move_dir(0, 1);
    Direction dummy_dir(1, 0);

    /*
     * Esperar que la posición del jugador luego del movimiento sea la resta de la
     * intersección con el obstáculo y el producto de la dirección de movimiento y
     * el radio del jugador
     * */
    Position intended_destination = initial_pos + move_dir * player_max_velocity;
    Position intersection = p2_pos + p2_pos.get_direction(intended_destination) * player_radius;
    Position expected = intersection - move_dir * player_radius;

    p1_ptr->start_moving(move_dir);
    p1_ptr->update(1);
    EXPECT_EQ(p1_ptr->pos, expected);
}

}  // namespace
