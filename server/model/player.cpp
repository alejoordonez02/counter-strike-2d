#include "server/model/player.h"

#include <memory>
#include <utility>

#include "common/direction.h"
#include "common/position.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"
#include "server/model/weapon.h"

/*
 * Constructor
 * */
Player::Player(int id, Position pos, std::unique_ptr<Equipment>&& equipment,
               std::weak_ptr<Map> map, float max_velocity, float acceleration,
               float radius, int money, int max_health):
    Hitbox(pos), id(id), map(map),
    physics(this->pos, max_velocity, acceleration, radius,
            this->map.lock()->get_collidables(), sorted_collidables_idx),
    action(std::make_unique<Idle>()), dir(), equipment(std::move(equipment)),
    current(*this->equipment->knife), max_health(max_health),
    health(max_health), alive(true), kills(0), money(money) {}

/*
 * Set current weapon
 * */
void Player::use_primary() { current = *equipment->primary; }
void Player::use_secondary() { current = *equipment->secondary; }
void Player::use_knife() { current = *equipment->knife; }

/*
 * Buy
 * */
bool Player::pay(const int& cost) {
    if (money < cost) return false;
    money -= cost;
    return true;
}

void Player::buy_primary(Weapon& weapon) {
    if (pay(weapon.get_cost())) {
        *equipment->primary = weapon;
        use_primary();
    }
}

void Player::buy_secondary(Weapon& weapon) {
    if (pay(weapon.get_cost())) {
        *equipment->secondary = weapon;
        use_secondary();
    }
}

void Player::buy_primary_ammo(const int& count) {
    if (pay(equipment->primary->get_ammo_cost() * count))
        equipment->primary->load_ammo(count);
}

void Player::buy_secondary_ammo(const int& count) {
    if (pay(equipment->secondary->get_ammo_cost() * count))
        equipment->secondary->load_ammo(count);
}
