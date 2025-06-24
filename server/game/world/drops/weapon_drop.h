#ifndef SERVER_WEAPON_DROP_H
#define SERVER_WEAPON_DROP_H

#include "drop.h"

class WeaponDrop: public Drop {
    std::shared_ptr<Weapon> weapon;

public:
    WeaponDrop(std::shared_ptr<Weapon> weapon, Position pos);

    std::shared_ptr<Weapon> get_weapon() const override;

    WeaponType get_type() const override;

    void push_drop_data(std::vector<WeaponDTO>& snapshot) override;
};

#endif
