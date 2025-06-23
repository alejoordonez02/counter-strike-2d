#include "weapon.h"

#include <memory>
#include <vector>

#include "server/game/world/random.h"

Weapon::Weapon(const int& damage, const int& ammo, const float& accuracy,
               const float& range, float fire_rate, const int& cost,
               const int& ammo_cost, float reload_time):
    damage(damage), ammo(ammo), accuracy(accuracy), range(range),
    fire_delay(1 / fire_rate), cost(cost), ammo_cost(ammo_cost),
    reload_time(reload_time) {}

void Weapon::attack(Position origin, Direction direction,
                    std::vector<std::shared_ptr<Hitbox>>& collidables,
                    const std::vector<size_t>& sorted_idx) {
    if (!fire_delay.is_done()) return;

    Trajectory t(origin, origin + direction * range);
    for (auto i : sorted_idx) {
        auto coll = collidables[i];
        if (coll->intersect(t)) {
            if (Random::get() < accuracy) coll->get_attacked(damage);

            ammo--;
            break;
        }
    }

    fire_delay.restart();
}

int Weapon::get_cost() const { return cost; }

int Weapon::get_ammo_cost() const { return ammo_cost; }

float Weapon::get_reload_time() { return reload_time; }
