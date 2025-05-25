#include "player.h"

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include "../../common/direction.h"
#include "../../common/position.h"

#include "collidable.h"
#include "map.h"
#include "trajectory.h"
#include "weapon.h"

Player::Player(const Position& pos, Map& map):
        Collidable(pos),
        map(map),
        kills(0),
        primary(Awp()),
        secondary(),
        current_weapon(primary),
        shield(0),
        health(100),
        alive(true) {}

void Player::move(const Direction& dir) { return (void)dir; }  // dummy
void Player::attack(const Position& destination) {
    Trajectory t(pos, destination);
    auto& collidable = map.get_collidable();
    auto sorted_idx = sort_by_distance_idx(collidable);
    for (size_t i: sorted_idx) {
        auto& c = collidable[i];
        if (c.get() == this)
            continue;  // skip self, probablemente sea mejor sacarlo de prepo en vez de checkear
                       // siempre
        if (t.intersects(c->get_pos())) {
            current_weapon.attack(*c);
            break;
        }
    }
}
void Player::get_attacked(const int& damage) {
    health -= (1 - shield) * damage;
    if (health <= 0)
        alive = false;
}
