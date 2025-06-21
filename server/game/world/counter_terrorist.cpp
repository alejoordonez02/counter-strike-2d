#include "counter_terrorist.h"

#include "ct_equipment.h"
#include "player.h"

void CounterTerrorist::teleport_to_spawn() { pos = map.lock()->get_ct_spawn(); }

CounterTerrorist::CounterTerrorist(int id, std::weak_ptr<Map> map,
                                   float max_velocity, float acceleration,
                                   float radius, int money, int health):
    Player(id, map.lock()->get_ct_spawn(), CTEquipment(), map, max_velocity,
           acceleration, radius, money, health) {}

void CounterTerrorist::defuse_bomb() {}
void CounterTerrorist::stop_defusing() {}
