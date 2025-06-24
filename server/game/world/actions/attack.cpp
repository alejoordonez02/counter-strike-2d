#include "attack.h"

/*
 * TODO: make this configurable
 * */
#define KILL_REWARD 800

Attack::Attack(Position& pos, Direction& dir, std::shared_ptr<Weapon> weapon,
               std::vector<std::shared_ptr<Hitbox>>& collidables,
               std::vector<size_t>& sorted_idx, int& kills, int& money):
    pos(pos), dir(dir), weapon(weapon), collidables(collidables),
    sorted_idx(sorted_idx), kills(kills), money(money) {}

void Attack::update(float /* dt */) {
    if (weapon->attack(pos, dir, collidables, sorted_idx)) {
        kills++;
        money += KILL_REWARD;
    };
}

bool Attack::is_attacking() const { return true; }
