#ifndef ATTACK_H
#define ATTACK_H

#include "../../server/model/player.h"
#include "../position.h"

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
