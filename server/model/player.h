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

public:
    Player(Position& pos, Map& map);

    /*
     * Both TT & CT commands
     * */
    virtual void move(const Direction& dir);
    virtual void attack(const Position& destination);
    virtual void drop_current();
    virtual void buy();

    virtual void get_attacked(const int& damage) override;

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

    ~Player() = default;
};

#endif
