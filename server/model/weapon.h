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
    int ammo_cost;

public:
    Weapon();

    Weapon(const int& damage, const int& ammo, const float& accuracy, const float& range,
           const int& cost, const int& ammo_cost);

    virtual void attack(const Position& origin, const Position& destination, Hitbox& coll);

    virtual void load_ammo(const int& count) { ammo += count; }

    virtual int get_cost() const;

    virtual int get_ammo_cost() const;

    virtual ~Weapon() = default;
};

#endif
