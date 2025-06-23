#include "counter_terrorist.h"

#include "actions/defuse_bomb.h"
#include "ct_equipment.h"
#include "player.h"

// TODO: make this configurable
#define TIME_TO_DEFUSE 10

void CounterTerrorist::teleport_to_spawn() { pos = map.lock()->get_ct_spawn(); }

CounterTerrorist::CounterTerrorist(int id, std::weak_ptr<Map> map,
                                   float max_velocity, float acceleration,
                                   float radius, int money, int health):
    Player(id, map.lock()->get_ct_spawn(), CTEquipment(), map, max_velocity,
           acceleration, radius, money, health) {}

void CounterTerrorist::restart() { respawn(); }

void CounterTerrorist::defuse_bomb() {
    auto bomb_state = map.lock()->get_bomb_state();
    if (bomb_state != BombState::PLANTED) return;
    auto bomb_pos = map.lock()->get_bomb_position();
    if (!physics.intersects(bomb_pos)) return;

    action = std::make_unique<DefuseBomb>(pos, map, TIME_TO_DEFUSE);
}
