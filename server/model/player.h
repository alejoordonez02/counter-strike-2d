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

class Player: public PlayerPhysics {
private:
    int kills;
    int money;

    int health;
    bool alive;

protected:
    Equipment equipment;
    Weapon& current;

    virtual bool pay(const int& cost);

public:
    Player(const Position& pos, const Direction& dir, Equipment&& equipment, Map& map);

    /*
     * Both TT & CT commands
     * */
    virtual void attack(const Position& destination);
    virtual void use_primary();
    virtual void use_secondary();
    virtual void use_knife();
    // virtual void drop_current();
    virtual void buy_primary(Weapon& weapon);
    virtual void buy_secondary(Weapon& weapon);
    virtual void buy_primary_ammo(const int& count);
    virtual void buy_secondary_ammo(const int& count);

    virtual void get_attacked(const int& damage) override;

    // virtual void update(float dt);

    /*
     * Terrorist
     * */
    virtual void plant_bomb();
    virtual void stop_planting();

    /*
     * Counter terrorist
     * */
    virtual void defuse_bomb();
    virtual void stop_defusing();

    ~Player() = default;
};

#endif
