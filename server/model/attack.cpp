#include "server/model/attack.h"

Attack::Attack(PlayerPhysics& physics, Position& pos, Direction& dir,
               Weapon& weapon, Map& map):
        physics(physics), pos(pos), dir(dir), weapon(weapon), map(map) {}

void Attack::update(float dt) {
    auto& collidables = map.get_collidables();
    auto sorted_idx = physics.get_distance_sorted_collidables_idx(collidables);
    weapon.attack(pos, dir, collidables, sorted_idx);
}
