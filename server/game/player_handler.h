#ifndef SERVER_PLAYER_HANDERL_H
#define SERVER_PLAYER_HANDERL_H

#include "common/network/connection.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/queue.h"
#include "player_commands/player_cmd_constructor.h"
#include "world/player.h"

class PlayerHandler {
private:
    Connection con;
    Queue<std::unique_ptr<DTO>> snapshots;
    Queue<std::unique_ptr<DTO>> commands;
    Receiver receiver;
    Sender sender;
    std::shared_ptr<Player> player;
    CmdConstructor constructor;

public:
    PlayerHandler(Connection&& con, std::shared_ptr<Player> player);

    void start();

    void play();

    void send_snapshot(const SnapshotDTO& snapshot);
};

#endif
