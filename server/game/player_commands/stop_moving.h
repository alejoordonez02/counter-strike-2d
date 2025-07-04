#ifndef SERVER_PLAYER_COMMANDS_STOP_MOVING_H
#define SERVER_PLAYER_COMMANDS_STOP_MOVING_H

#include "common/network/dtos/stop_moving_dto.h"
#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Stop moving
 * */
class StopMoving: public Command {
public:
    explicit StopMoving() {}

    void execute(Player& p) const override { p.stop_moving(); }

    ~StopMoving() = default;
};

#endif
