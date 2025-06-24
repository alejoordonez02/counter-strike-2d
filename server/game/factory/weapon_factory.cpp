#include "weapon_factory.h"

#include <map>

#include "weapon.h"
#include "weapon_config.h"
#include "weapons.h"

WeaponFactory::WeaponFactory(const std::map<WeaponName, WeaponConfig>& config):
    config(config) {}

std::shared_ptr<Weapon> WeaponFactory::create(WeaponName name) const {
    WeaponConfig config;
    config = this->config.at(name);
    return std::make_shared<Weapon>(
        name, config.type, config.damage, config.accuracy, config.range,
        config.bullet_size, config.fire_rate, config.reload_time,
        config.ammo_capacity, config.starting_ammo, config.cost,
        config.ammo_cost);
}
