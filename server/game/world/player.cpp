#include "player.h"

#include <iostream>
#include <memory>
#include <stdexcept>

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
Player::Player(int id, Position pos, std::shared_ptr<Weapon> primary,
               std::shared_ptr<Weapon> secondary, std::shared_ptr<Weapon> knife,
               std::weak_ptr<Map> map, float max_velocity, float acceleration,
               float radius, int money, int health,
               std::shared_ptr<WeaponFactory> weapon_factory):
    Hitbox(pos), id(id), map(map),
    physics(this->pos, max_velocity, acceleration, radius,
            this->map.lock()->get_collidables(), sorted_collidables_idx),
    action(std::make_unique<Idle>()), dir(), primary(std::move(primary)),
    secondary(std::move(secondary)), knife(std::move(knife)), shield(0),
    current(this->knife), max_health(health), health(health), alive(true),
    kills(0), money(money), weapon_factory(weapon_factory) {}

/*
 * Update
 * */
void Player::update(float dt) {
    if (!alive) return;
    physics.update(dt);
    current->update(dt);
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
    health -= (1 - shield) * damage;
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
 * Pickup and drop stuff on the ground
 * */
void Player::pickup() {
    if (!alive) return;

    std::unique_ptr<Drop> item = map.lock()->pickup(pos);
    if (!item) return;

    if (item->get_type() == WeaponType::KNIFE) return;
    if (item->get_type() == WeaponType::BOMB) return give_bomb();

    std::shared_ptr<Weapon> weapon;
    weapon = get_weapon(item->get_type());
    if (weapon) drop(std::move(weapon));

    switch (item->get_type()) {
        case WeaponType::PRIMARY:
            primary = item->get_weapon();
            current = primary;
            break;
        case WeaponType::SECONDARY:
            secondary = item->get_weapon();
            current = secondary;
            break;
        default:
            throw std::runtime_error("Player: pickup: unknown weapon type");
    }
}

void Player::drop(std::shared_ptr<Weapon> weapon) {
    if (weapon->get_type() == WeaponType::KNIFE) return;
    switch (weapon->get_type()) {
        case WeaponType::PRIMARY:
            if (primary == weapon) primary = nullptr;
            break;
        case WeaponType::SECONDARY:
            if (secondary == weapon) secondary = nullptr;
            break;
        default:
            throw std::runtime_error("Player: drop: unknown weapon type");
    }

    map.lock()->drop(std::make_unique<WeaponDrop>(std::move(weapon), pos));
    current = knife;
}

void Player::drop() {
    if (!alive || !current) return;
    auto weapon = current;
    drop(std::move(weapon));
}

/*
 * Weapon private selector
 * */
std::shared_ptr<Weapon> Player::get_weapon(WeaponType type) {
    switch (type) {
        case WeaponType::PRIMARY:
            return primary;
        case WeaponType::SECONDARY:
            return secondary;
        case WeaponType::KNIFE:
            return knife;
        default:
            throw std::runtime_error("Player: get_weapon: unknown weapon type");
    }
}

/*
 * Set current weapon
 * */
void Player::use_weapon(const WeaponType& type) {
    auto weapon = get_weapon(type);
    if (!weapon) return;
    current = weapon;
}

void Player::start_reloading() { action = std::make_unique<Reload>(current); }

/*
 * Buy
 * */
bool Player::pay(const int& cost) {
    if (money < cost) return false;
    money -= cost;
    return true;
}

void Player::buy_weapon(WeaponName weapon_name) {
    auto weapon = weapon_factory->create(weapon_name);
    if (!pay(weapon->get_cost())) return;
    auto slot = get_weapon(weapon->get_type());
    slot = weapon;
}

void Player::buy_ammo(WeaponType type, int count) {
    if (count <= 0 || type == WeaponType::KNIFE) return;
    auto weapon = get_weapon(type);
    if (!weapon) return;
    if (!pay(current->get_ammo_cost() * count)) return;
    weapon->add_ammo(count);
}

/*
 * Get snapshot of the current state of the player
 * */
std::shared_ptr<PrivatePlayerDTO> Player::get_private_data() const {
    auto data = std::make_shared<PrivatePlayerDTO>();
    data->player_id = id;
    data->player_hp = health;
    data->current_weapon = current->get_private_data();
    data->total_money = money;
    data->rounds_won = 0;  // TODO: ésto lo sabe World!
    data->total_kills = kills;
    return data;
}

PlayerDTO Player::get_data() const {
    PlayerDTO data;
    data.player_id = id;
    data.x = pos.x;
    data.y = pos.y;
    data.current_weapon = current->get_data();
    data.aim_x = dir.x;
    data.aim_y = dir.y;
    data.is_walking = physics.is_moving();
    data.is_dead = !alive;
    return data;
}
