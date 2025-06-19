#include "client_session.h"
#include "common/network/protocol.h"

bool ClientSession::is_offline() { return _is_offline; }

const std::string& ClientSession::get_username() { return username; }

void ClientSession::start_lobby_phase() {
    lobby = new ClientLobby(this, con, username, _is_offline, game_monitor);
    lobby->start();
}

void ClientSession::end_lobby_phase() {
    lobby->join();
    delete lobby;
}

void ClientSession::set_player(std::shared_ptr<Player> p) {
    p_handler = new PlayerHandler(con, p);
}

PlayerHandler* ClientSession::start_game_phase() {
    end_lobby_phase();
    con.send_single(LobbySerial::GAME_HAS_BEGUN);
    p_handler->start();

    return p_handler;
}

void ClientSession::end_game_phase(/* std::shared_ptr<GameSnapshot> o std::shared_ptr<GameFinishedDTO> */) {
    delete(p_handler);
    start_lobby_phase();
}

void ClientSession::force_terminate() { // falta definir cierre de server
    con.destroy_socket();
    end_lobby_phase();
}