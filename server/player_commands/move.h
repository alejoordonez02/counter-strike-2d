#ifndef MOVE_H
#define MOVE_H

#include "../model/player.h"
#include "../../common/direction.h"

#include "command.h"

/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;

public:
    Move(Direction d);
    void execute(Player& p) const override;
    Direction get_direction() const;
};

#endif
