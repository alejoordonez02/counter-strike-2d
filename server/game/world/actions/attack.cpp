#include "attack.h"

Attack::Attack(Position& pos, Direction& dir, Weapon& weapon,
               std::vector<std::shared_ptr<Hitbox>>& collidables,
               std::vector<size_t>& sorted_idx):
    pos(pos), dir(dir), weapon(weapon), collidables(collidables),
    sorted_idx(sorted_idx) {}

/*
 * Sería lógico que sea Attack el que updatee el arma pero de esa manera el
 * jugador podría disparar, iterar entre dos armas y no tener nada de tiempo de
 * cancelación (op awp)
 * */
void Attack::update(float /* dt */) {
    weapon.attack(pos, dir, collidables, sorted_idx);
}
