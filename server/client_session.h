#ifndef SERVER_CLIENT_SESSION_H
#define SERVER_CLIENT_SESSION_H

#include <memory>
#include <string>

#include "common/network/connection.h"

#include "server/client_lobby.h"

#include "common/network/socket/socket.h"
#include "server/player_handler.h"

class GameMonitor;
class Player;

class ClientSession {
private:
    Connection con;

    std::string username;
    GameMonitor& game_monitor;
    ClientLobby* lobby;
    PlayerHandler* p_handler;

    bool _is_offline;


public:
    ClientSession(Socket&& s, GameMonitor& gm): 
            con(std::move(s)), game_monitor(gm), _is_offline(false) {}


    bool is_offline();
    const std::string& get_username();
    void start_lobby_phase();
    void end_lobby_phase();
    void set_player(std::shared_ptr<Player> p);
    PlayerHandler* start_game_phase();
    void end_game_phase();
    void force_terminate();

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator=(const ClientSession&) = delete;

    ClientSession(ClientSession&&) = default;
    ClientSession& operator=(ClientSession&&) = default;

    ~ClientSession() = default;
};

#endif
