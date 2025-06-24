#include "server.h"

Server::Server(const std::string& servname):
    clients(), acceptor(servname, clients, game_maker) {}

void Server::start() {
    acceptor.start();

    std::string start;
    do {
        getline(std::cin, start);
    } while (start != "s");

    acceptor.stop();
    acceptor.join();
}
