#ifndef SERVER_PLAYER_COMMANDS_DROP_H
#define SERVER_PLAYER_COMMANDS_DROP_H

#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Drop current weapon
 * */
class DropCurrent: public Command {
public:
    explicit DropCurrent() {}

    void execute(Player& p) const override { p.drop(); }

    ~DropCurrent() = default;
};

#endif
