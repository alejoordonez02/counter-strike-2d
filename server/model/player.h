#ifndef SERVER_MODEL_PLAYER_H
#define SERVER_MODEL_PLAYER_H

#include <iostream>
#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "common/snapshot.h"
#include "server/model/action_strategy.h"
#include "server/model/attack.h"
#include "server/model/equipment.h"
#include "server/model/idle.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"
#include "server/model/weapon.h"

class Player: public Hitbox {
protected:
    std::weak_ptr<Map> map;  // o shared_ptr& ?

private:
    int id;
    /*
     * Esta es una alternativa para excluir self de los collidables del mapa. El
     * problema es el ownership, con weak_ptr no es trivial y shared está mal
     * std::vector<std::shared_ptr<Hitbox>> other_collidables;
     * */
    std::vector<size_t> sorted_collidables_idx;
    PlayerPhysics physics;
    std::unique_ptr<ActionStrategy> action;
    Direction dir;
    std::unique_ptr<Equipment> equipment;
    Weapon& current;
    int max_health;
    int health;
    bool alive;
    int kills;
    int money;

    bool pay(const int& cost);

    void stop_action() { action = std::make_unique<Idle>(); }

public:
    Player(int id, Position pos, std::unique_ptr<Equipment>&& equipment,
           std::weak_ptr<Map> map, float max_velocity, float acceleration,
           float radius, int money, int health);

    void update(float dt) {
        if (!alive)
            return;

        physics.update(dt);
        current.update(dt);
        action->update(dt);
    }

    virtual void teleport_to_spawn() {}

    PlayerData get_data() const {
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

    void restart() {
        teleport_to_spawn();
        health = max_health;
        alive = true;
    }

    bool is_alive() { return alive; }

    std::optional<Position> intersect(const Trajectory& t) const override {
        if (!alive)
            return std::nullopt;

        return physics.intersect(t);
    }

    void get_attacked(int damage) override {
        alive -= (1 - equipment->shield) * damage;
        if (health <= 0)
            alive = false;
    }

    virtual void start_moving(Direction dir) { physics.start_moving(dir); }

    void stop_moving() {
        std::cout << "Player: stop_moving();\n";
        physics.stop_moving();
    }

    virtual void start_attacking() {
        action = std::make_unique<Attack>(pos, dir, current,
                                          map.lock()->get_collidables(),
                                          sorted_collidables_idx);
    }

    void stop_attacking() { stop_action(); }

    void aim(Direction dir) { this->dir = dir; }

    void use_primary();
    void use_secondary();
    void use_knife();

    void buy_primary(Weapon& weapon);
    void buy_secondary(Weapon& weapon);
    void buy_primary_ammo(const int& count);
    void buy_secondary_ammo(const int& count);

    /*
     * Terrorist
     * */
    virtual void plant_bomb() {}
    virtual void stop_planting() {}

    /*
     * Counter terrorist
     * */
    virtual void defuse_bomb() {}
    virtual void stop_defusing() {}

    virtual ~Player() = default;
};

#endif
