#ifndef SERVER_PLAYER_COMMANDS_DROP_BOMB_H
#define SERVER_PLAYER_COMMANDS_DROP_BOMB_H

#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Drop bomb
 * */
class DropBomb: public Command {
public:
    explicit DropBomb() {}

    void execute(Player& p) const override { p.drop_bomb(); }

    ~DropBomb() = default;
};

#endif
