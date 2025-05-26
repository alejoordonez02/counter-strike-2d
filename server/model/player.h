#ifndef PLAYER_H
#define PLAYER_H

#include "../../common/direction.h"  //
#include "../../common/position.h"   // mover a model
                                     /* */

#include "../../common/direction.h"
#include "../../common/position.h"

#include "collidable.h"
#include "map.h"
#include "weapon.h"

class Player: public Collidable {
private:
    Map& map;
    int kills;
    Weapon primary;
    Weapon secondary;
    Weapon& current_weapon;
    int shield; /* entre 0 y 1 */
    int health;
    bool alive;

public:
    Player(const Position& pos, Map& map);

    virtual void move(const Direction& dir);
    virtual void attack(const Position& destination);
    virtual void get_attacked(const int& damage) override;
    ~Player() = default;
};

#endif
