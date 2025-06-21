#include "terrorist.h"

#include "equipment/tt_equipment.h"
#include "player.h"

void Terrorist::teleport_to_spawn() { pos = map.lock()->get_tt_spawn(); }

Terrorist::Terrorist(int id, std::weak_ptr<Map> map, float max_velocity,
                     float acceleration, float radius, int money, int health,
                     std::optional<Bomb> bomb):
    Player(id, map.lock()->get_tt_spawn(), TTEquipment(), map, max_velocity,
           acceleration, radius, money, health),
    bomb(bomb) {}

void Terrorist::plant_bomb() {}
void Terrorist::stop_planting() {}
