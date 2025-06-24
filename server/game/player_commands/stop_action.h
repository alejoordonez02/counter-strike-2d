#ifndef SERVER_PLAYER_COMMANDS_STOP_ACTION_H
#define SERVER_PLAYER_COMMANDS_STOP_ACTION_H

#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Stop action
 * */
class StopAction: public Command {
public:
    explicit StopAction() {}

    void execute(Player& p) const override { p.stop_action(); }

    ~StopAction() = default;
};

#endif
