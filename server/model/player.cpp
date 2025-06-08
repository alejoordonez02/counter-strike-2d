#include "player.h"

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include "../../common/direction.h"
#include "../../common/position.h"

#include "map.h"
#include "player_physics.h"
#include "weapon.h"

#define PLAYER_VELOCITY 1.0
#define PLAYER_ACCELERATION 1.0
#define PLAYER_RADIUS 1.0
#define PLAYER_MONEY 500

Player::Player(Position pos, Equipment&& equipment, Map& map):
        pos(pos),
        dir(Direction()),
        health(100),
        alive(true),
        map(map),
        equipment(std::move(equipment)),
        physics(pos, health, this->equipment.shield, alive, PLAYER_VELOCITY, PLAYER_ACCELERATION,
                PLAYER_RADIUS, map),
        action(std::make_unique<Idle>()),
        kills(0),
        money(PLAYER_MONEY),
        current(*this->equipment.knife) {}

/*
 * Set current weapon
 * */
void Player::use_primary() { current = *equipment.primary; }

void Player::use_secondary() { current = *equipment.secondary; }

void Player::use_knife() { current = *equipment.knife; }

/*
 * Buy
 * */
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
