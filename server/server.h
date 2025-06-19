#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "game_setup.h"
#include "network/acceptor.h"
#include "server/client_handler.h"
#include "server/game_loop.h"

class Server {
private:
    std::vector<std::unique_ptr<ClientHandler>> clients;
    Acceptor acceptor;

public:
    Server(const std::string& servname):
        clients(), acceptor(servname, clients) {}

    void start() {
        acceptor.start();

        std::string start;
        do {
            getline(std::cin, start);
        } while (start != "s");

        acceptor.stop();
        acceptor.join();

        GameLoop game = GameSetup::setup(clients);
        game.start();
        game.join();
    }
};

#endif
