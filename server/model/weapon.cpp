#include "weapon.h"

#include "random.h"

Weapon::Weapon() {}

Weapon::Weapon(const int& damage, const int& ammo, const float& accuracy):
        damage(damage), ammo(ammo), accuracy(accuracy) {}

int Weapon::get_damage() { return damage; }

/*
 * attack() lo vamos a tener que sobrecargar según el arma, además
 * por el modo en el que esté la misma... patrón Strategy va como piña
 * */
void Weapon::attack(Collidable& coll) {
    if (Random::get(0, 1) < accuracy) {
        coll.get_attacked(damage);
        ammo--;
    }
}

Awp::Awp(): Weapon(100, 30, 1) {}
