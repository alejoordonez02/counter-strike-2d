#include "client_session.h"

bool ClientSession::is_offline() { return _is_offline; }

const std::string& ClientSession::get_username() { return username; }

bool ClientSession::try_pop_command(std::unique_ptr<Command>& cmd_p) {
    std::unique_ptr<DTO> dto_p;
    if (recv_q.try_pop(dto_p)) {
        cmd_p = cmd_ctr.construct(std::move(dto_p));
        return true;
    }
    return false;
}

bool ClientSession::try_push_game_update(
        /* std::shared_ptr<GameSnapshotDTO> g_snap */) {
    // send_q.try_push(std::move(g_snap)) // el move no hace falta pero para
    // probar la queue mejorada send_q.try_push( info especifica del player )
}

void ClientSession::start_lobby_phase() {
    lobby = new ClientLobby(this, con, username, _is_offline, game_monitor);
    lobby->start();
}

void ClientSession::end_lobby_phase() {
    lobby->join();
    delete lobby;
}

void ClientSession::start_game_phase() {
    end_lobby_phase();
    send_q.reset();
    recv_q.reset();
    sndr = new Sender(con, send_q);
    rcvr = new Receiver(con, recv_q);
    sndr->start();
    rcvr->start();
}

void ClientSession::end_game_phase(/* std::shared_ptr<GameSnapshot> o std::shared_ptr<GameFinishedDTO> */) {
    // send_q.push(); // asegura push de update final
    send_q.close();
    sndr->join();
    delete sndr;

    Socket s = con.release_socket();
    std::unique_ptr<DTO> discard;
    recv_q.try_pop(discard);  // desbloquear receiver por si estaba en push con
                              // queue llena
    rcvr->join();
    con.acquire_socket(std::move(s));
    delete rcvr;

    start_lobby_phase();
}

void ClientSession::force_terminate() {  // falta definir cierre de server
    con.destroy_socket();
    end_lobby_phase();
}
