#ifndef SERVER_PLAYER_HANDLER_H
#define SERVER_PLAYER_HANDLER_H

#include "common/queue.h"
#include "common/network/dto.h"
#include "common/network/sender.h"
#include "common/network/receiver.h"
#include "server/cmd_constructor.h"
#include "player_commands/command.h"
#include "server/model/player.h"

class PlayerHandler {
private:
    Connection& con;
    Queue<std::shared_ptr<DTO>> send_q;
    Queue<std::unique_ptr<DTO>> recv_q;
    Sender* sndr;
    Receiver* rcvr;

    std::shared_ptr<Player> player;
    CmdConstructor cmd_ctr;

public:
    PlayerHandler(Connection& c, std::shared_ptr<Player> p);

    void start();
    bool try_play();
    bool try_push_game_update(/* std::shared_ptr<GameSnapshotDTO> g_snap */);
    void push_finished_game(/* std::shared_ptr<GameSnapshot> o std::shared_ptr<GameFinishedDTO> */);

    PlayerHandler(const PlayerHandler&) = delete;
    PlayerHandler& operator=(const PlayerHandler&) = delete;

    PlayerHandler(PlayerHandler&&) = default;
    PlayerHandler& operator=(PlayerHandler&&) = default;

    ~PlayerHandler() = default;
};

#endif