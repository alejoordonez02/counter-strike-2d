#include "player.h"

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include "../../common/direction.h"
#include "../../common/position.h"

#include "map.h"
#include "player_physics.h"
#include "weapon.h"

#define PLAYER_VELOCITY 1
#define PLAYER_ACCELERATION 1
#define PLAYER_RADIUS 1
#define PLAYER_MONEY 500

Player::Player(const Position& pos, const Direction& dir, Equipment&& equipment, Map& map):
        PlayerPhysics(pos, dir, PLAYER_VELOCITY, PLAYER_ACCELERATION, PLAYER_RADIUS, map),
        equipment(std::move(equipment)),
        kills(0),
        money(PLAYER_MONEY),
        health(100),
        alive(true),
        current(*this->equipment.knife) {}

void Player::attack(const Position& destination) {
    auto& collidable = map.get_collidable();
    auto sorted_idx = sort_by_distance_idx(collidable);
    for (size_t i: sorted_idx) {
        auto& c = collidable[i];
        if (c.get() == this)
            continue;  // skip self
        current.attack(pos, destination, *c);
        break;
    }
}

void Player::use_primary() { current = *equipment.primary; }

void Player::use_secondary() { current = *equipment.secondary; }

void Player::use_knife() { current = *equipment.knife; }

bool Player::pay(const int& cost) {
    if (money < cost)
        return false;
    money -= cost;
    return true;
}

void Player::buy_primary(Weapon& weapon) {
    if (pay(weapon.get_cost())) {
        *equipment.primary = weapon;
        use_primary();
    }
}

void Player::buy_secondary(Weapon& weapon) {
    if (pay(weapon.get_cost())) {
        *equipment.secondary = weapon;
        use_secondary();
    }
}

void Player::buy_primary_ammo(const int& count) {
    if (pay(equipment.primary->get_ammo_cost() * count))
        equipment.primary->load_ammo(count);
}

void Player::buy_secondary_ammo(const int& count) {
    if (pay(equipment.secondary->get_ammo_cost() * count))
        equipment.secondary->load_ammo(count);
}

void Player::get_attacked(const int& damage) {
    health -= (1 - equipment.shield) * damage;
    if (health <= 0)
        alive = false;
}

/*
 * Terrorist
 * */
void Player::plant_bomb() {}
void Player::stop_planting() {}

/*
 * Counter terrorist
 * */
void Player::defuse_bomb() {}
void Player::stop_defusing() {}
