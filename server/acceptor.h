#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <string>
#include <utility>
#include <vector>

#include "client_handler.h"
#include "common/network/connection.h"
#include "common/network/socket/socket.h"
#include "common/thread.h"
#include "game_maker.h"

#define CLOSE_BOTH_STREAMS 2

class Acceptor: public Thread {
private:
    Socket listener;
    std::vector<std::unique_ptr<ClientHandler>>& clients;
    GameMaker& game_maker;

public:
    Acceptor(const std::string& servname,
             std::vector<std::unique_ptr<ClientHandler>>& clients,
             GameMaker& game_maker):
        listener(servname.c_str()), clients(clients), game_maker(game_maker) {}

    void run() override {
        while (should_keep_running()) {
            try {
                Socket skt = listener.accept();
                Connection con(std::move(skt));
                auto client =
                    std::make_unique<ClientHandler>(std::move(con), game_maker);
                client->start();
                clients.push_back(std::move(client));
            } catch (...) {
                if (!should_keep_running()) break;
            }
        }
    }

    void stop() override {
        Thread::stop();
        listener.shutdown(CLOSE_BOTH_STREAMS);
    }

    ~Acceptor() = default;
};

#endif
