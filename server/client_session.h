#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include <memory>
#include <string>

#include "../common/network/connection.h"
#include "../common/queue.h"
#include "../common/network/dto.h"
#include "../common/network/sender.h"
#include "../common/network/receiver.h"
#include "client_lobby.h"
#include "game_monitor.h"
#include "cmd_constructor.h"
#include "player_commands/command.h"
#include "common/network/socket/socket.h"

class ClientSession {
private:
    Connection con;
    Queue<std::shared_ptr<DTO>> send_q;
    Queue<std::unique_ptr<DTO>> recv_q;
    Sender* sndr;
    Receiver* rcvr;

    std::string username;
    GameMonitor& game_monitor;
    ClientLobby* lobby;
    bool _is_offline;

    CmdConstructor cmd_ctr;

public:
    ClientSession(Socket&& s, GameMonitor& gm): 
            con(std::move(s)), game_monitor(gm), _is_offline(false) {}


    bool is_offline();
    const std::string& get_username();
    bool try_pop_command(std::unique_ptr<Command>& cmd_p);
    bool try_push_game_update(/* std::shared_ptr<GameSnapshotDTO> g_snap */);
    void start_lobby_phase();
    void end_lobby_phase();
    void start_game_phase();
    void end_game_phase(/* std::shared_ptr<GameSnapshot> o std::shared_ptr<GameFinishedDTO> */);
    void force_terminate();

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator=(const ClientSession&) = delete;

    ClientSession(ClientSession&&) = default;
    ClientSession& operator=(ClientSession&&) = default;

    ~ClientSession() = default;
};

#endif
