#ifndef SERVER_WORLD_EQUIPMENT_WEAPONS_H
#define SERVER_WORLD_EQUIPMENT_WEAPONS_H

#include "weapon.h"

/* Weapon(int damage, float accuracy, float range, float fire_rate, int cost,
           int ammo_cost, int ammo, int max_loaded_ammo, float reload_time); */
class Fist: public Weapon {
public:
    Fist(): Weapon(0, 0, 0, 0, 0, 0, 0, 0, 0) {}
};

class Knife: public Weapon {
public:
    Knife(): Weapon(33, 1, 1.5, 0, 0, 0, 0, 0, 0) {}
};

class Glock: public Weapon {
public:
    Glock(): Weapon(20, 0.9, 50, 0.2, 200, 1, 15, 15, 2) {}
};

class Ak47: public Weapon {
public:
    Ak47(): Weapon(30, 0.8, 400, 4, 300, 1, 90, 30, 4) {}
};

class M3: public Weapon {
public:
    M3(): Weapon(40, 0.7, 20, 0.5, 400, 2, 8, 8, 3) {}
};

class Awp: public Weapon {
public:
    Awp(): Weapon(100, 0.95, 100, 1, 500, 3, 90, 30, 4) {}
};

#endif
