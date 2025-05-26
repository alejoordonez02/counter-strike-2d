#ifndef WEAPON_H
#define WEAPON_H

#include "collidable.h"

class Weapon {
private:
    int damage;
    int ammo;
    float accuracy; /* entre 0 y 1, es una proba */
public:
    Weapon();
    Weapon(const int& damage, const int& ammo, const float& accuracy);
    int get_damage();
    void attack(Collidable& coll);
};

class Awp: public Weapon {
public:
    Awp();
};

#endif
