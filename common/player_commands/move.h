#ifndef MOVE_H
#define MOVE_H

#include "../../server/player.h"
#include "../direction.h"
#include "../serializer.h"

#include "command.h"

class Serializer;

/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;

public:
    Move(Direction d): dir(d) {}

    void execute(Player& p) const override;
    std::string serialize() const override { return Serializer::serialize_move(dir); }
    Direction get_dir() const;
};

#endif
