#ifndef SERVER_WORLD_EQUIPMENT_WEAPON_H
#define SERVER_WORLD_EQUIPMENT_WEAPON_H

#include <algorithm>
#include <memory>
#include <vector>

#include "server/game/world/physics/hitbox.h"
#include "server/game/world/timer.h"

class Weapon {
private:
    int damage;
    float accuracy;
    float range;
    Timer fire_delay;
    int cost;
    int ammo_cost;
    int ammo;
    int max_loaded_ammo;
    int loaded_ammo;
    float reload_time;

public:
    Weapon(int damage, float accuracy, float range, float fire_rate, int cost,
           int ammo_cost, int ammo, int max_loaded_ammo, float reload_time);

    void update(float dt) { fire_delay.update(dt); }

    virtual void attack(Position origin, Direction direction,
                        std::vector<std::shared_ptr<Hitbox>>& collidables,
                        const std::vector<size_t>& sorted_idx);

    virtual void reload();

    virtual int get_cost() const;

    virtual int get_ammo_cost() const;

    float get_reload_time();

    virtual ~Weapon() = default;
};

#endif
