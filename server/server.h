#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "server/acceptor.h"
#include "server/client_handler.h"
#include "server/game_maker.h"

class Server {
private:
    std::vector<std::unique_ptr<ClientHandler>> clients;
    GameMaker game_maker;
    Acceptor acceptor;

public:
    Server(const std::string& servname):
        clients(), acceptor(servname, clients, game_maker) {}

    void start() {
        acceptor.start();

        std::string start;
        do {
            getline(std::cin, start);
        } while (start != "s");

        acceptor.stop();
        acceptor.join();
    }
};

#endif
