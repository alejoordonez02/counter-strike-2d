#include "weapon.h"

#include <cstdio>
#include <memory>
#include <vector>

#include "server/game/world/random.h"

Weapon::Weapon(WeaponName name, WeaponType type, float damage, float accuracy,
               float range, float bullet_size, float fire_rate,
               float reload_time, int ammo_capacity, int starting_ammo,
               int cost, int ammo_cost):
    name(name), type(type), damage(damage), accuracy(accuracy), range(range),
    fire_delay(1 / fire_rate), reload_time(reload_time),
    ammo_capacity(ammo_capacity), loaded_ammo(ammo_capacity),
    ammo(starting_ammo - ammo_capacity), cost(cost), ammo_cost(ammo_cost) {}

void Weapon::attack(Position origin, Direction direction,
                    std::vector<std::shared_ptr<Hitbox>>& collidables,
                    const std::vector<size_t>& sorted_idx) {
    if (loaded_ammo <= 0 || !fire_delay.is_done()) return;

    Trajectory t(origin, origin + direction * range, bullet_size);
    for (auto i : sorted_idx) {
        auto coll = collidables[i];
        if (coll->intersect(t)) {
            if (Random::get() < accuracy) coll->get_attacked(damage);
            break;
        }
    }

    loaded_ammo--;
    fire_delay.restart();
}

void Weapon::reload() {
    int to_load = std::min(ammo, ammo_capacity - loaded_ammo);
    loaded_ammo += to_load;
    ammo -= to_load;
}

int Weapon::get_cost() const { return cost; }

int Weapon::get_ammo_cost() const { return ammo_cost; }

float Weapon::get_reload_time() { return reload_time; }

PrivateWeaponDTO Weapon::get_private_data() const {
    PrivateWeaponDTO data;
    data.name = name;
    data.total_ammo = ammo + loaded_ammo;
    data.loaded_ammo = loaded_ammo;
    return data;
}

WeaponName Weapon::get_data() const { return name; }
