#include <cmath>
#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "gtest/gtest.h"
#include "server/model/equipment.h"
#include "server/model/map.h"
#include "server/model/player.h"
#include "server/model/weapons.h"

class CollisionsTest: public ::testing::Test {
protected:
    int player_id = 0;
    float player_radius = 1.0f;
    float player_max_velocity = 1.0f;
    float player_acceleration = 100.0f;  // trigger max velocity
    int player_money = 800;
    int player_max_health = 100;

    std::shared_ptr<Map> map;

    std::shared_ptr<Player> get_player(Position& pos_ref) {
        auto equipment = std::make_unique<Equipment>(
                std::make_unique<Fist>(), std::make_unique<Glock>(),
                std::make_unique<Knife>(), 0);

        return std::make_shared<Player>(
                player_id, pos_ref, std::move(equipment), map,
                player_max_velocity, player_acceleration, player_radius,
                player_money, player_max_health);
    }

    void EXPECT_POS_EQ(const Position& pos, const Position& other) const {
        EXPECT_NEAR(pos.x, other.x, 1e-7);
        EXPECT_NEAR(pos.y, other.y, 1e-7);
    }

    void SetUp() override { map = std::make_shared<Map>(); }
};

TEST_F(CollisionsTest, PlayerCanWalkFreelyIfTheraAreNotAnyObstacles) {
    Position initial_pos(0, 0);
    auto player = get_player(initial_pos);

    EXPECT_POS_EQ(initial_pos, player->get_position());

    player->start_moving(Direction(1, 0));
    player->update(1);
    EXPECT_POS_EQ(Position(1, 0), player->get_position());

    player->start_moving(Direction(0, 1));
    player->update(1);
    EXPECT_POS_EQ(Position(1, 1), player->get_position());

    player->start_moving(Direction(1, 1));
    player->update(1);
    float diag = 1.0f / std::sqrt(2.0f);
    EXPECT_POS_EQ(Position(1.0f + diag, 1.0f + diag), player->get_position());

    player->start_moving(Direction(-1, 0));
    player->update(1);
    EXPECT_POS_EQ(Position(diag, 1.0f + diag), player->get_position());
}

TEST_F(CollisionsTest, PlayerCannotWalkThroughAnotherPlayer) {
    Position p1_pos(0, 0);
    Position p2_pos(0, 2.5f);

    auto p1 = get_player(p1_pos);
    auto p2 = get_player(p2_pos);

    map->add_collidable(p2);
    map->add_collidable(p1);

    p1->start_moving(Direction(0, 1));
    p1->update(1);

    EXPECT_POS_EQ(Position(0, 0.5f), p1->get_position());
}

/*
 * Suprimo ésta prueba hasta que la interfaz del juego sea accesible para dos
 * jugadores y así poder probar visualmente su comportamiento, de otra forma
 * algunas cosas son demasiado difíciles de determinar
 * */
/* TEST_F(CollisionsTest, PlayerCannotSideWalkThroughAnotherPlayer) {
    Position p1_initial_pos(0, 0);
    Position p2_initial_pos(1.0f, 1.8f);

    auto p1 = get_player(p1_initial_pos);
    auto p2 = get_player(p2_initial_pos);

    map.add_collidable(*p2);
    map.add_collidable(*p1);

    p1->start_moving(Direction(1, 0));
    p1->update(1);

    float expected_x_contact = 1.0f - std::sqrt(0.76f);

    EXPECT_POS_EQ(Position(expected_x_contact, 0.0f), p1->get_position());
} */
