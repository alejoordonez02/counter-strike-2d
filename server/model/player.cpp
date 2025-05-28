#include "player.h"

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include "../../common/direction.h"
#include "../../common/position.h"

#include "circle.h"
#include "map.h"
#include "weapon.h"

#define PLAYER_RADIUS 1

Player::Player(const Position& pos, Map& map):
        Circle(pos, PLAYER_RADIUS),
        map(map),
        kills(0),
        primary(Awp()),
        secondary(),
        current_weapon(primary),
        shield(0),
        health(100),
        alive(true),
        velocity(1) {}

void Player::move(const Direction& dir) { pos += dir * velocity; }

void Player::attack(const Position& destination) {
    auto& collidable = map.get_collidable();
    auto sorted_idx = sort_by_distance_idx(collidable);
    for (size_t i: sorted_idx) {
        auto& c = collidable[i];
        if (c.get() == this)
            continue;  // skip self
        current_weapon.attack(pos, destination, *c);
        break;
    }
}

void Player::get_attacked(const int& damage) {
    health -= (1 - shield) * damage;
    if (health <= 0)
        alive = false;
}
