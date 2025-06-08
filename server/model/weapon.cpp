#include "weapon.h"

#include "random.h"

Weapon::Weapon() {}

Weapon::Weapon(const int& damage, const int& ammo, const float& accuracy, const float& range,
               const int& cost, const int& ammo_cost):
        damage(damage),
        ammo(ammo),
        accuracy(accuracy),
        range(range),
        cost(cost),
        ammo_cost(ammo_cost) {}

void Weapon::attack(const Position& origin, const Position& destination, Hitbox& coll) {
    Trajectory t(origin, destination * range);
    if (coll.intersect(t) and Random::get() < accuracy) {
        coll.get_attacked(damage);
        ammo--;
    }
}

int Weapon::get_cost() const { return cost; }

int Weapon::get_ammo_cost() const { return ammo_cost; }
