#ifndef SERVER_CONFIG_WEAPON_CONFIG_H
#define SERVER_CONFIG_WEAPON_CONFIG_H

struct WeaponConfig {
    int damage;
    int ammo;
    float accuracy;
    float range;
    float fire_delay;
    int cost;
    int ammo_cost;
};

#endif
