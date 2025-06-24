#include "terrorist.h"

#include "actions/plant_bomb.h"
#include "player.h"

#define TIME_TO_PLANT 10

Terrorist::Terrorist(int id, std::shared_ptr<Weapon> primary,
                     std::shared_ptr<Weapon> secondary,
                     std::shared_ptr<Weapon> knife, std::weak_ptr<Map> map,
                     float max_velocity, float acceleration, float radius,
                     int money, int health,
                     std::shared_ptr<WeaponFactory> weapon_factory):
    Player(id, map.lock()->get_tt_spawn(), primary, secondary, knife, map,
           max_velocity, acceleration, radius, money, health, weapon_factory) {}

void Terrorist::teleport_to_spawn() { pos = map.lock()->get_tt_spawn(); }

void Terrorist::restart() {
    respawn();
    _has_bomb = false;
}

bool Terrorist::has_bomb() const { return _has_bomb; }

void Terrorist::give_bomb() { _has_bomb = true; }

void Terrorist::drop_bomb() {
    if (!_has_bomb) return;
    map.lock()->drop(std::make_unique<BombDrop>(pos));
    _has_bomb = false;
}

void Terrorist::start_planting() {
    if (!_has_bomb) return;
    auto bomb_site = map.lock()->get_bomb_site();
    bool on_bomb_site = false;
    for (auto s : bomb_site)
        if (s.intersects(pos)) {
            on_bomb_site = true;
            break;
        }

    if (!on_bomb_site) return;
    action = std::make_unique<PlantBomb>(_has_bomb, pos, map, TIME_TO_PLANT);
}
