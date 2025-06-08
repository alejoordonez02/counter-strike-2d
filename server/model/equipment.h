#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <memory>

#include "weapon.h"

struct Equipment {
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    float shield;

    Equipment(std::unique_ptr<Weapon>&& primary, std::unique_ptr<Weapon>&& secondary,
              std::unique_ptr<Weapon>&& knife, const float& shield):
            primary(std::move(primary)),
            secondary(std::move(secondary)),
            knife(std::move(knife)),
            shield(shield) {}
};

#endif
