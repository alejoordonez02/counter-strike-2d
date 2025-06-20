#include "server/world/player.h"

#include <memory>
#include <utility>

#include "common/direction.h"
#include "common/position.h"
#include "server/world/actions/idle.h"
#include "server/world/equipment/weapon.h"
#include "server/world/map.h"
#include "server/world/physics/player_physics.h"

void Player::stop_action() { action = std::make_unique<Idle>(); }

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
 * Update
 * */
void Player::update(float dt) {
    if (!alive) return;
    physics.update(dt);
    current.update(dt);
    action->update(dt);
}

/*
 * Restart
 * */
void Player::restart() {
    teleport_to_spawn();
    health = max_health;
    alive = true;
}

bool Player::is_alive() { return alive; }

std::optional<Position> Player::intersect(const Trajectory& t) const {
    if (!alive) return std::nullopt;
    return physics.intersect(t);
}

void Player::get_attacked(int damage) {
    health -= (1 - equipment->shield) * damage;
    if (health <= 0) alive = false;
}

void Player::start_moving(Direction dir) { physics.start_moving(dir); }
void Player::stop_moving() { physics.stop_moving(); }

void Player::start_attacking() {
    action = std::make_unique<Attack>(pos, dir, current,
                                      map.lock()->get_collidables(),
                                      sorted_collidables_idx);
}

void Player::stop_attacking() { stop_action(); }

void Player::aim(Direction dir) { this->dir = dir; }

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

/*
 * Get snapshot of the current state of the player
 * */
PlayerData Player::get_data() const {
    PlayerData data;
    data.player_id = id;
    data.x = pos.x;
    data.y = pos.y;
    data.aim_x = dir.x;
    data.aim_y = dir.y;
    data.is_walking = physics.is_moving();
    data.is_dead = alive;
    return data;
}
