#ifndef PLAYER_H
#define PLAYER_H

#include "common/direction.h"
#include "common/position.h"

#include "action_strategy.h"
#include "attack.h"
#include "equipment.h"
#include "idle.h"
#include "map.h"
#include "player_physics.h"
#include "weapon.h"

class Player {
private:
    Position pos;
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
    Map& map;
    Equipment equipment;
    Weapon& current;

public:
    Player(Position pos, Equipment&& equipment, Map& map);

    /*
     * Update
     * */
    void update(float dt) {
        physics.update(dt);
        action->update(dt);
    }

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
    void plant_bomb() {}
    void stop_planting() {}

    /*
     * Counter terrorist
     * */
    void defuse_bomb() {}
    void stop_defusing() {}

    /*
     * Destructor
     * */
    virtual ~Player() = default;
};

#endif
