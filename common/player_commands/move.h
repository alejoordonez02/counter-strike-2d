#ifndef MOVE_H
#define MOVE_H

#include "../../server/model/player.h"
#include "../direction.h"

#include "command.h"

class Serializer;

/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;

public:
    Move(Direction d);
    void execute(Player& p) const override;
    Direction get_dir() const;
};

#endif
