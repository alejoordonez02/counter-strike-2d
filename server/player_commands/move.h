#ifndef MOVE_H
#define MOVE_H

#include "command.h"
#include "../model/player.h"
#include "../../common/direction.h"

/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;

public:
    explicit Move(const Direction& d): dir(d) {}

    void execute(Player& p) const override { p.move(dir); }

    ~Move() = default;
};

#endif
