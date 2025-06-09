#include "server/model/weapon.h"

#include <vector>

#include "server/model/random.h"

Weapon::Weapon() {}

Weapon::Weapon(const int& damage, const int& ammo, const float& accuracy,
               const float& range, const int& cost, const int& ammo_cost):
        damage(damage),
        ammo(ammo),
        accuracy(accuracy),
        range(range),
        cost(cost),
        ammo_cost(ammo_cost) {}

void Weapon::attack(Position origin, Direction direction,
                    std::vector<std::reference_wrapper<Hitbox>>& collidables,
                    const std::vector<size_t>& sorted_idx) {
    /*
     * Recibe un vector de colisionables y de índices que los ordena,
     * los recorre en orden y si alguno interseca con la trayectoria del
     * ataque, le pega (con probabilidad de miss), resta munición y corta
     * */
    Trajectory t(origin, origin + direction * range);
    for (auto i : sorted_idx) {
        auto& coll = collidables[i].get();
        if (coll.intersect(t) && Random::get() < accuracy) {
            coll.get_attacked(damage);
            ammo--;
            break;
        }
    }
}

int Weapon::get_cost() const { return cost; }

int Weapon::get_ammo_cost() const { return ammo_cost; }
