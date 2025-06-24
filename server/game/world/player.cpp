#include "player.h"

#include <iostream>
#include <memory>

#include "actions/idle.h"
#include "common/direction.h"
#include "common/position.h"
#include "equipment/weapon.h"
#include "map.h"
#include "physics/player_physics.h"
#include "reload.h"

void Player::stop_action() { action = std::make_unique<Idle>(); }

/*
 * Constructor
 * */
Player::Player(int id, Position pos, const Equipment& equipment,
               std::weak_ptr<Map> map, float max_velocity, float acceleration,
               float radius, int money, int max_health):
    Hitbox(pos), id(id), map(map),
    physics(this->pos, max_velocity, acceleration, radius,
            this->map.lock()->get_collidables(), sorted_collidables_idx),
    action(std::make_unique<Idle>()), dir(), equipment(equipment),
    current(this->equipment.primary), max_health(max_health),
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
void Player::respawn() {
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
    health -= (1 - equipment.shield) * damage;
    if (health <= 0) alive = false;
}

void Player::start_moving(Direction dir) { physics.start_moving(dir); }
void Player::stop_moving() { physics.stop_moving(); }

void Player::start_attacking() {
    std::cout << "Player: start_attacking\n";
    action = std::make_unique<Attack>(pos, dir, current,
                                      map.lock()->get_collidables(),
                                      sorted_collidables_idx);
}

void Player::aim(Direction dir) { this->dir = dir; }

/*
 * Set current weapon
 * */
void Player::use_primary() { current = equipment.primary; }
void Player::use_secondary() { current = equipment.secondary; }
void Player::use_knife() { current = equipment.knife; }

void Player::start_reloading() { action = std::make_unique<Reload>(current); }

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
        equipment.primary = weapon;
        use_primary();
    }
}

void Player::buy_secondary(Weapon& weapon) {
    if (pay(weapon.get_cost())) {
        equipment.secondary = weapon;
        use_secondary();
    }
}

/*
 * Get snapshot of the current state of the player
 * */
std::shared_ptr<PrivatePlayerDTO> Player::get_private_data() const {
    auto data = std::make_shared<PrivatePlayerDTO>();
    data->player_id = id;
    data->player_hp = health;
    data->current_weapon = current.get_private_data();
    data->total_money = money;
    data->rounds_won = 0;  // ésto lo sabe World!
    data->total_kills = kills;
    return data;
}

PlayerDTO Player::get_data() const {
    PlayerDTO data;
    data.player_id = id;
    data.x = pos.x;
    data.y = pos.y;
    data.current_weapon = current.get_data();
    data.aim_x = dir.x;
    data.aim_y = dir.y;
    data.is_walking = physics.is_moving();
    data.is_dead = !alive;
    return data;
}
