#ifndef ATTACK_H
#define ATTACK_H

#include "command.h"
#include "../model/player.h"
#include "../../common/position.h"

/*
 * Attack
 * */
class Attack: public Command {
private:
    Position pos;

public:
    Attack(const Position& p): pos(p) {}

    void execute(Player& p) const override { p.attack(pos); }
    
    ~Attack() = default;
};

#endif
