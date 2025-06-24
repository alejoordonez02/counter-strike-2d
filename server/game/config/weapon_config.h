#ifndef SERVER_CONFIG_WEAPON_CONFIG_H
#define SERVER_CONFIG_WEAPON_CONFIG_H

#include "common/weapons.h"

struct WeaponConfig {
    WeaponType type;
    float damage;
    float accuracy;
    float range;
    float bullet_size;
    float fire_rate;
    float reload_time;
    int ammo_capacity;
    int starting_ammo;
    int cost;
    int ammo_cost;
};

#endif
