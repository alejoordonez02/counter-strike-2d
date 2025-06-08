#ifndef PLAYER_H
#define PLAYER_H

#include "common/direction.h"
#include "common/position.h"

#include "equipment.h"
#include "map.h"
#include "player_physics.h"
#include "weapon.h"

enum class MovementState { IDLE, MOVING };
enum class ActionState { NONE, ATTACKING, RELOADING, PLANTING, DEFUSING };

class Player {
private:
    Position pos;
    int health;
    bool alive;
    PlayerPhysics physics;

    int kills;
    int money;

    bool pay(const int& cost);

protected:
    Map& map;
    Equipment equipment;
    Weapon& current;

public:
    Player(Position pos, Equipment&& equipment, Map& map);

    /*
     * Update
     * */
    void update(float dt);

    /*
     * Move
     * */
    void start_moving(Direction dir) { physics.start_moving(dir); }
    void stop_moving() { physics.stop_moving(); }

    /*
     * Attack
     * */
    void start_attacking() {}
    void stop_attacking() {}

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
