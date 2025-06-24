#include "weapon_drop.h"

WeaponDrop::WeaponDrop(std::shared_ptr<Weapon> weapon, Position pos):
    Drop(pos), weapon(std::move(weapon)) {}

std::shared_ptr<Weapon> WeaponDrop::get_weapon() const { return weapon; }

WeaponType WeaponDrop::get_type() const { return weapon->get_type(); }

void WeaponDrop::push_drop_data(std::vector<WeaponDTO>& snapshot) {
    snapshot.push_back(WeaponDTO(weapon->get_name(), pos));
}
