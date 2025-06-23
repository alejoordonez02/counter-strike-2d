#include "terrorist.h"

#include "actions/plant_bomb.h"
#include "equipment/tt_equipment.h"
#include "player.h"

#define TIME_TO_PLANT 10

void Terrorist::teleport_to_spawn() { pos = map.lock()->get_tt_spawn(); }

Terrorist::Terrorist(int id, std::weak_ptr<Map> map, float max_velocity,
                     float acceleration, float radius, int money, int health):
    Player(id, map.lock()->get_tt_spawn(), TTEquipment(), map, max_velocity,
           acceleration, radius, money, health) {}

void Terrorist::restart() {
    respawn();
    has_bomb = false;
}

void Terrorist::give_bomb() { has_bomb = true; }

void Terrorist::plant_bomb() {
    if (!has_bomb) return;
    auto bomb_site = map.lock()->get_bomb_site();
    bool on_bomb_site = false;
    for (auto s : bomb_site)
        if (s.intersects(pos)) {
            on_bomb_site = true;
            break;
        }

    if (!on_bomb_site) return;
    action = std::make_unique<PlantBomb>(has_bomb, pos, map, TIME_TO_PLANT);
}
