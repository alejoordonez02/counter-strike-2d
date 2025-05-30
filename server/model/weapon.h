#ifndef WEAPON_H
#define WEAPON_H

#include "hitbox.h"

class Weapon {
private:
    int damage;
    int ammo;
    float accuracy; /* entre 0 y 1, es una proba */
    float range;
    int cost;

public:
    Weapon();

    Weapon(const int& damage, const int& ammo, const float& accuracy, const float& range,
           const int& cost);

    virtual void attack(const Position& origin, const Position& destination, Hitbox& coll);

    virtual int get_cost() const;

    virtual ~Weapon() = default;
};

#endif
