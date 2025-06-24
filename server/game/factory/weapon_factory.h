#ifndef SERVER_GAME_FACTORY_WEAPON_FACTORY_H
#define SERVER_GAME_FACTORY_WEAPON_FACTORY_H

#include <map>

#include "weapon.h"
#include "weapon_config.h"
#include "weapons.h"

class WeaponFactory {
private:
    std::map<WeaponName, WeaponConfig> config;

public:
    WeaponFactory(const std::map<WeaponName, WeaponConfig>& config);

    std::shared_ptr<Weapon> create(WeaponName name) const;
};

#endif
