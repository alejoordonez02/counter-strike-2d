#include "bomb_drop.h"

BombDrop::BombDrop(Position pos): Drop(pos) {}

std::shared_ptr<Weapon> BombDrop::get_weapon() const { return nullptr; }

WeaponType BombDrop::get_type() const { return WeaponType::BOMB; }

void BombDrop::push_drop_data(std::vector<WeaponDTO>& snapshot) {
    snapshot.push_back(WeaponDTO(WeaponName::BOMB, pos));
}
