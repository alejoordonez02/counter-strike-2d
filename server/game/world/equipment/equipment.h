#ifndef SERVER_MODEL_EQUIPMENT_H
#define SERVER_MODEL_EQUIPMENT_H

#include "weapon.h"
#include "weapons.h"

struct Equipment {
    Weapon primary;
    Weapon secondary;
    Knife knife;
    float shield;

    Equipment(const Weapon& primary, const Weapon& secondary, float shield):
        primary(primary), secondary(secondary), knife(), shield(shield) {}
};

#endif
