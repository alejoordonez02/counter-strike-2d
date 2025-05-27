#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include "../common/network/connection.h"
#include "../common/queue.h"
#include "../common/network/sender.h"
#include "../common/network/receiver.h"
#include "game_monitor.h"

class ClientSession {
private:
    Connection conn;
    Queue<> send_q;
    Queue<> recv_q;
    Sender sndr;
    Receiver rcvr;
    GameMonitor& game_monitor;
    bool _is_finished;

public:
    ClientSession(Socket&& s, GameMonitor& gm): conn(std::move(s)), game_monitor(gm), _is_finished(false) {
        ClientSetup setup(conn, game_monitor);
        setup.start();
        setup.join();
        sndr.start();
        rcvr.start();
    }

    bool is_finished() { return _is_finished; }

    void push_game_update() {}

    void terminate() {
        conn.destroy_socket()
		send_q.close()
		recv_q.close()
		sender.join()
		receiver.join()
        _is_finished = true;
    }

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator=(const ClientSession&) = delete;

    ClientSession(ClientSession&&) = delete;
    ClientSession& operator=(ClientSession&&) = delete;

    ~ClientSession() = default;
};

#endif
