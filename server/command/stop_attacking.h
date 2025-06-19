#ifndef SERVER_PLAYER_COMMANDS_STOP_ATTACKING_H
#define SERVER_PLAYER_COMMANDS_STOP_ATTACKING_H

#include "common/network/dtos/stop_attacking_dto.h"
#include "server/model/player.h"
#include "server/player_commands/command.h"

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
