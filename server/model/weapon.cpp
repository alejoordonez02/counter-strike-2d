#include "weapon.h"

#include "random.h"

Weapon::Weapon() {}

Weapon::Weapon(const int& damage, const int& ammo, const float& accuracy, const float& range,
               const int& cost):
        damage(damage), ammo(ammo), accuracy(accuracy), range(range), cost(cost) {}

void Weapon::attack(const Position& origin, const Position& destination, Hitbox& coll) {
    Trajectory t(origin, destination * range);
    if (coll.intersects(t) and Random::get() < accuracy) {
        coll.get_attacked(damage);
        ammo--;
    }
}
