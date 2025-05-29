#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include "../common/network/connection.h"
#include "../common/queue.h"
#include "../common/network/dto.h"
#include "../common/network/sender.h"
#include "../common/network/receiver.h"
#include "game_monitor.h"
#include "client_setup.h"

class ClientSession {
private:
    Connection con;
    Queue<DTO> send_q;
    Queue<DTO> recv_q;
    Sender sndr;
    Receiver rcvr;
    GameMonitor& game_monitor;
    bool _is_finished;

public:
    ClientSession(Socket&& s, GameMonitor& gm): 
            con(std::move(s)), sndr(con, send_q), rcvr(con, recv_q), game_monitor(gm), _is_finished(false) {
        // ClientSetup setup(con, game_monitor);
        // setup.start();
        // setup.join();
        sndr.start();
        rcvr.start();
    }

    bool is_finished() { return _is_finished; }

    void push_game_update(/* std::shared_ptr<GameSnapshot> */) {}

    void terminate() {
        // con.destroy_socket();
		send_q.close();
		recv_q.close();
		sndr.join();
		rcvr.join();
        _is_finished = true;
    }

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator=(const ClientSession&) = delete;

    ClientSession(ClientSession&&) = delete;
    ClientSession& operator=(ClientSession&&) = delete;

    ~ClientSession() = default;
};

#endif
