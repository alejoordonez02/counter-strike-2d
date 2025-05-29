#include "weapon.h"

#include "random.h"

Weapon::Weapon() {}

Weapon::Weapon(const int& damage, const int& ammo, const float& accuracy, const float& range):
        damage(damage), ammo(ammo), accuracy(accuracy), range(range) {}

int Weapon::get_damage() { return damage; }

/*
 * attack() lo vamos a tener que sobrecargar según el arma, además
 * por el modo en el que esté la misma... patrón Strategy va como piña
 * */
void Weapon::attack(const Position& origin, const Position& destination, Hitbox& coll) {
    Trajectory t(origin, destination * range);
    if (coll.intersects(t) and Random::get() < accuracy) {
        coll.get_attacked(damage);
        ammo--;
    }
}

Awp::Awp(): Weapon(100, 30, 1, 100) {}
