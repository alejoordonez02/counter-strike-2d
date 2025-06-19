#include "player_handler.h"

PlayerHandler::PlayerHandler(Connection& c, std::shared_ptr<Player> p): con(c), player(p) {}

void PlayerHandler::start() {
    sndr = new Sender(con, send_q);
    rcvr = new Receiver(con, recv_q);
    sndr->start();
    rcvr->start();
}

bool PlayerHandler::try_play() {
    std::unique_ptr<DTO> dto_p;
    if (not recv_q.try_pop(dto_p))
        return false;
    
    auto cmd_p = cmd_ctr.construct(std::move(dto_p));
    cmd_p->execute(*player);

    return true;
}

bool PlayerHandler::try_push_game_update(/* std::shared_ptr<GameSnapshotDTO> g_snap */) {
    // send_q.try_push(std::move(g_snap)) // el move no hace falta pero para probar la queue mejorada
    // send_q.try_push( info especifica del player ) // player->get_full_player_DTO()
}

void PlayerHandler::push_finished_game(/* std::shared_ptr<GameSnapshot> o std::shared_ptr<GameFinishedDTO> */) {
    // send_q.push(); // asegura push de update final
    send_q.close();
    sndr->join();
    delete sndr;

    Socket s = con.release_socket();
    std::unique_ptr<DTO> discard;
    recv_q.try_pop(discard); // desbloquear receiver por si estaba en push con queue llena
    rcvr->join();
    con.acquire_socket(std::move(s));
    delete rcvr;
}


