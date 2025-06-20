#ifndef SERVER_WORLD_EQUIPMENT_WEAPON_H
#define SERVER_WORLD_EQUIPMENT_WEAPON_H

#include <memory>
#include <vector>

#include "server/world/physics/hitbox.h"
#include "server/world/timer.h"

class Weapon {
private:
    int damage;
    int ammo;
    float accuracy;
    float range;
    Timer fire_delay;
    int cost;
    int ammo_cost;

public:
    Weapon(const int& damage, const int& ammo, const float& accuracy,
           const float& range, float fire_rate, const int& cost,
           const int& ammo_cost);

    void update(float dt) { fire_delay.update(dt); }

    virtual void attack(Position origin, Direction direction,
                        std::vector<std::shared_ptr<Hitbox>>& collidables,
                        const std::vector<size_t>& sorted_idx);

    virtual void load_ammo(const int& count) { ammo += count; }

    virtual int get_cost() const;

    virtual int get_ammo_cost() const;

    virtual ~Weapon() = default;
};

#endif
