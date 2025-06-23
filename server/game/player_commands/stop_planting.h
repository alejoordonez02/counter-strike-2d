#ifndef SERVER_PLAYER_COMMANDS_STOP_PLANTING_H
#define SERVER_PLAYER_COMMANDS_STOP_PLANTING_H

#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Stop planting
 * */
class StopPlanting: public Command {
public:
    explicit StopPlanting() {}

    void execute(Player& p) const override { p.stop_planting(); }

    ~StopPlanting() = default;
};

#endif
