#ifndef SERVER_PLAYER_COMMANDS_STOP_ATTACKING_H
#define SERVER_PLAYER_COMMANDS_STOP_ATTACKING_H

#include "server/player_commands/command.h"
#include "server/world/player.h"

/*
 * Stop attacking
 * */
class StopAttacking: public Command {
public:
    explicit StopAttacking() {}

    void execute(Player& p) const override { p.stop_attacking(); }

    ~StopAttacking() = default;
};

#endif
