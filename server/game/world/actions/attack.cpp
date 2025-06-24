#include "attack.h"

Attack::Attack(Position& pos, Direction& dir, std::shared_ptr<Weapon> weapon,
               std::vector<std::shared_ptr<Hitbox>>& collidables,
               std::vector<size_t>& sorted_idx):
    pos(pos), dir(dir), weapon(weapon), collidables(collidables),
    sorted_idx(sorted_idx) {}

void Attack::update(float /* dt */) {
    weapon->attack(pos, dir, collidables, sorted_idx);
}
