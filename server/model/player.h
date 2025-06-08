#ifndef PLAYER_H
#define PLAYER_H

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include "../../common/direction.h"
#include "../../common/position.h"

#include "circle.h"
#include "equipment.h"
#include "map.h"
#include "weapon.h"

class Player: public Circle {
private:
    float velocity;

    int kills;
    int money;

    int health;
    bool alive;

protected:
    Map& map;

    Equipment equipment;
    Weapon& current;

    virtual bool pay(const int& cost);

public:
    Player(const Position& pos, Equipment&& equipment, Map& map);

    /*
     * Both TT & CT commands
     * */
    virtual void start_moving(const Direction& dir) {dir + dir;}
    virtual void start_attacking() {}

    virtual void move(const Direction& dir);
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
