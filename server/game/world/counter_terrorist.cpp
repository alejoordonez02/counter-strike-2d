#include "counter_terrorist.h"

#include "actions/defuse_bomb.h"
#include "player.h"

// TODO: make this configurable
#define TIME_TO_DEFUSE 10

CounterTerrorist::CounterTerrorist(
    int id, std::shared_ptr<Weapon> primary, std::shared_ptr<Weapon> secondary,
    std::shared_ptr<Weapon> knife, std::weak_ptr<Map> map, float max_velocity,
    float acceleration, float radius, int money, int health,
    std::shared_ptr<WeaponFactory> weapon_factory):
    Player(id, map.lock()->get_ct_spawn(), primary, secondary, knife, map,
           max_velocity, acceleration, radius, money, health, weapon_factory) {}

void CounterTerrorist::teleport_to_spawn() { pos = map.lock()->get_ct_spawn(); }

uint8_t CounterTerrorist::get_team() const { return 1; }

void CounterTerrorist::restart() { respawn(); }

void CounterTerrorist::start_defusing() {
    auto bomb_state = map.lock()->get_bomb_state();
    if (bomb_state != BombState::PLANTED) return;
    auto bomb_pos = map.lock()->get_bomb_position();
    if (!physics.intersects(bomb_pos)) return;

    action = std::make_unique<DefuseBomb>(pos, map, TIME_TO_DEFUSE);
}

void CounterTerrorist::give_bomb() {
    /*
     * papa caliente, la agarra y la suelta
     * */
    map.lock()->drop(std::make_unique<BombDrop>(pos));
}

bool CounterTerrorist::has_bomb() const override { return false; }
