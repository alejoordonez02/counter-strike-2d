#ifndef ATTACK_H
#define ATTACK_H

#include "../model/player.h"
#include "../../common/position.h"

#include "command.h"

/*
 * Attack
 * */
class Attack: public Command {
private:
    Position pos;

public:
    Attack(const Position& pos);
    void execute(Player& p) const override;
    Position get_position() const;
};

#endif
