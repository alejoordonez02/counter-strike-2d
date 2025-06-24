#ifndef SERVER_GAME_WORLD_DROP_H
#define SERVER_GAME_WORLD_DROP_H

class Drop {};
/* #include "common/position.h"
#include "equipment/weapon.h"
// #include "player.h"

class Player;

class Drop {
private:
    Position pos;

public:
    Drop(const Position& pos): pos(pos) {}

    Position get_position() const { return pos; }

    virtual void pickup(Player& player) = 0;
};

class WeaponDrop: public Drop {
private:
    Weapon weapon;

public:
    WeaponDrop(const Position& pos, Weapon weapon): Drop(pos), weapon(weapon)
    {}

    void pickup(Player& player) override {}
};

class BombDrop: public Drop {
public:
    BombDrop(const Position& pos): Drop(pos) {}

    void pickup(Player& player) override { player.give_bomb(); }
}; */

#endif
