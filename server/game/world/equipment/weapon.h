#ifndef SERVER_WORLD_EQUIPMENT_WEAPON_H
#define SERVER_WORLD_EQUIPMENT_WEAPON_H

#include <memory>
#include <vector>

#include "common/network/dtos/private_weapon_dto.h"
#include "common/weapons.h"
#include "server/game/world/physics/hitbox.h"
#include "server/game/world/timer.h"

class Weapon {
private:
    WeaponName name;
    WeaponType type;

    float damage;
    float accuracy;
    float range;
    float bullet_size;

    Timer fire_delay;
    float reload_time;

    int ammo_capacity;
    int loaded_ammo;
    int ammo;

    int cost;
    int ammo_cost;

public:
    Weapon(WeaponName name, WeaponType type, float damage, float accuracy,
           float range, float bullet_size, float fire_rate, float reload_time,
           int ammo_capacity, int starting_ammo, int cost, int ammo_cost);

    void update(float dt) { fire_delay.update(dt); }

    virtual void attack(Position origin, Direction direction,
                        std::vector<std::shared_ptr<Hitbox>>& collidables,
                        const std::vector<size_t>& sorted_idx);

    virtual void reload();

    void add_ammo(int count);

    /*
     * Getters
     * */
    WeaponType get_type() const;

    virtual int get_cost() const;

    virtual int get_ammo_cost() const;

    float get_reload_time();

    WeaponName get_data() const;

    PrivateWeaponDTO get_private_data() const;

    virtual ~Weapon() = default;
};

#endif
