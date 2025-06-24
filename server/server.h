#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "acceptor.h"
#include "client_handler.h"
#include "game/game_maker.h"

class Server {
private:
    std::vector<std::unique_ptr<ClientHandler>> clients;
    GameMaker game_maker;
    Acceptor acceptor;

public:
    Server(const std::string& servname);

    void start();
};

#endif
