#ifndef SERVER_MODEL_PLAYER_H
#define SERVER_MODEL_PLAYER_H

#include <memory>

#include "common/direction.h"
#include "common/position.h"
#include "server/model/action_strategy.h"
#include "server/model/attack.h"
#include "server/model/equipment.h"
#include "server/model/idle.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"
#include "server/model/weapon.h"

#define PLAYER_VELOCITY 1.0
#define PLAYER_ACCELERATION 1.0
#define PLAYER_RADIUS 1.0
#define PLAYER_MONEY 500
#define PLAYER_MAX_HEALTH 100

class Player {
private:
    Direction dir;
    int health;
    bool alive;
    PlayerPhysics physics;
    std::unique_ptr<ActionStrategy> action;

    int kills;
    int money;

    bool pay(const int& cost);

    void stop_action() { action = std::make_unique<Idle>(); }

protected:
    Position pos;
    Map& map;
    Equipment equipment;
    Weapon& current;

    friend class Game;
    PlayerPhysics& get_physics() { return physics; }

    virtual void teleport_to_spawn() = 0;

public:
    Player(Position pos, Equipment&& equipment, Map& map);

    /*
     * Update
     * */
    void update(float dt) {
        if (!alive)
            return;

        current.update(dt);
        physics.update(dt);
        action->update(dt);
    }

    /*
     * Restart/respawn
     * */
    void restart() {
        teleport_to_spawn();
        health = PLAYER_MAX_HEALTH;
        alive = true;
    }

    /*
     * Alive?
     * */
    bool is_alive() { return alive; }

    /*
     * Move
     * */
    virtual void start_moving(Direction dir) { physics.start_moving(dir); }

    void stop_moving() { physics.stop_moving(); }

    /*
     * Attack
     * */
    virtual void start_attacking() {
        action = std::make_unique<Attack>(physics, pos, dir, current, map);
    }

    void stop_attacking() { stop_action(); }

    /*
     * Aim
     * */
    void aim(Direction dir) { this->dir = dir; }

    /*
     * Set current weapon
     * */
    void use_primary();
    void use_secondary();
    void use_knife();

    /*
     * Buy
     * */
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

    /*
     * Destructor
     * */
    virtual ~Player() = default;
};

#endif
