#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <string>
#include <vector>

#include "client_handler.h"
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
             GameMaker& game_maker);

    void run() override;

    void stop() override;

    ~Acceptor() = default;
};

#endif
