#ifndef WEAPON_H
#define WEAPON_H

#include "hitbox.h"

class Weapon {
private:
    int damage;
    int ammo;
    float accuracy; /* entre 0 y 1, es una proba */
    float range;

public:
    Weapon();
    Weapon(const int& damage, const int& ammo, const float& accuracy, const float& range);
    int get_damage();
    void attack(const Position& origin, const Position& destination, Hitbox& coll);
};

class Awp: public Weapon {
public:
    Awp();
};

#endif
