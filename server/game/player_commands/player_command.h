#ifndef SERVER_PLAYER_COMMANDS_COMMAND_H
#define SERVER_PLAYER_COMMANDS_COMMAND_H

#include "server/game/world/player.h"

class Command {
protected:
    Command() = default;

public:
    virtual void execute(Player& p) const = 0;

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    Command(Command&&) = default;
    Command& operator=(Command&&) = default;

    virtual ~Command() = default;
};

#endif
