#ifndef SERVER_PLAYER_COMMANDS_PICKUP_H
#define SERVER_PLAYER_COMMANDS_PICKUP_H

#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Pickup
 * */
class Pickup: public Command {
public:
    explicit Pickup() {}

    void execute(Player& p) const override { p.pickup(); }

    ~Pickup() = default;
};

#endif
