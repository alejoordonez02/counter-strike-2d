#ifndef SERVER_PLAYER_COMMANDS_STOP_ATTACKING_H
#define SERVER_PLAYER_COMMANDS_STOP_ATTACKING_H

#include "player_command.h"
#include "server/game/world/player.h"

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
