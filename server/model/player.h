#ifndef PLAYER_H
#define PLAYER_H

#include "../../common/direction.h"
#include "../../common/position.h"

class Player {
public:
    virtual void move(const Direction& dir) { return (void)dir; }
    virtual void attack(const Position& pos) { return (void)pos; }
    virtual ~Player() = default;
};

#endif
