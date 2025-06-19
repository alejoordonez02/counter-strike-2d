#ifndef CLIENT_LOBBY_H
#define CLIENT_LOBBY_H

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <memory>

#include "common/thread.h"
#include "common/network/connection.h"
#include "game_monitor.h"
#include "common/network/protocol.h"
#include "common/network/dtos/game_details_dto.h"
#include "common/map_name.h"

class ClientSession;

class ClientLobby: public Thread {
private:
    ClientSession* c_session;
    Connection& conn;
    std::string& c_uname;
    bool& c_offline;
    GameMonitor& gm;

public:
    ClientLobby(ClientSession* cs, Connection& c, std::string& un, bool& off, GameMonitor& gm): 
            c_session(cs), conn(c), c_uname(un), c_offline(off), gm(gm) {}


    void run() override {
        try {
            if (not is_valid_username(c_uname))
                handle_username_change();

            bool lobby_over = false;
            while (not lobby_over) {
                uint8_t op_type = conn.receive_single();
                switch (op_type) {
                    case LobbySerial::CHANGE_USERNAME:
                        handle_username_change();
                        break;
                    case LobbySerial::LIST_GAMES:
                        handle_list_games();
                        break;
                    case LobbySerial::CREATE_GAME:
                        lobby_over = handle_create_game();
                        break;
                    case LobbySerial::JOIN_GAME:
                        lobby_over = handle_join_game();
                        break;
                    case LobbySerial::GET_GAME_DETAILS:
                        handle_get_game_details();
                        break;
                    case LobbySerial::BEGIN_GAME:
                        lobby_over = handle_begin_game();
                        break;
                    case LobbySerial::EXIT_SERVER:
                        c_offline = true;
                        gm.remove_username(c_uname);
                        return;
                    default:
                        throw std::runtime_error("ClientLobby error: unknown operation received"); // que lo agarre un catch
                }
            }
        } catch (const std::runtime_error& err) { // cierre de server
        }
    }

    ~ClientLobby() = default;

private:
    bool is_valid_username(const std::string& u) {
        if (u.empty())
            return false;
        bool has_spaces = std::any_of(u.begin(), u.end(), [](unsigned char ch) {return std::isspace(ch);});
        if (has_spaces)
            return false;

        return true;
    }

    std::string receive_str() {
        std::vector<uint8_t> msg = conn.receive_msg();
        return std::string(msg.begin(), msg.end());
    }

    void handle_username_change() {
        std::string prev_usrn = c_uname;
        while (true) {
            std::string usrn = receive_str();
            if (is_valid_username(usrn) && gm.add_username(usrn)) { // agregar chequeo usernames unicos
                c_uname = usrn;
                gm.remove_username(prev_usrn);
                conn.send_single(LobbySerial::SUCCESS);
                break;
            } else {
                conn.send_single(LobbySerial::FAILURE);
            }
        }
    }

    void handle_list_games() {
        std::vector<std::unique_ptr<GameDetailsDTO>> list = gm.list_games();
        conn.send_single(static_cast<uint8_t>(list.size()));

        for (auto& gd : list) {
            conn.send_msg(gd->serialize());
        }
    }

    bool handle_create_game() {
        std::string game_name = receive_str();
        MapName map_name = static_cast<MapName>(conn.receive_single());
        Team team = static_cast<Team>(conn.receive_single());
        bool success = gm.create_game(c_session, game_name, map_name, team);
        if (success)
            conn.send_single(LobbySerial::SUCCESS);
        else
            conn.send_single(LobbySerial::FAILURE);

        return success;
    }

    bool handle_join_game() {
        std::string game_name = receive_str();
        Team team = static_cast<Team>(conn.receive_single());
        bool success = gm.join_game(c_session, game_name, team);
        if (success)
            conn.send_single(LobbySerial::SUCCESS);
        else
            conn.send_single(LobbySerial::FAILURE);

        return success;
    }

    void handle_get_game_details() {
        std::string game_name = receive_str();
        auto details = gm.get_game_details(game_name);
        conn.send_msg(details->serialize());
    }

    bool handle_begin_game() {
        std::string game_name = receive_str();
        gm.begin_game(game_name);

        return true;
    }
};

#endif
