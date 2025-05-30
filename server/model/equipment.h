#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <memory>

#include "weapons.h"

struct Equipment {
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    int shield;

    Equipment():
            primary(std::make_unique<Fist>()),
            secondary(std::make_unique<Glock>()),
            knife(std::make_unique<Knife>()),
            shield(0) {}
};

#endif
