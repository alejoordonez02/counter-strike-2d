#include "acceptor.h"

#include <string>
#include <utility>
#include <vector>

#include "client_handler.h"
#include "common/network/connection.h"
#include "common/network/socket/socket.h"
#include "common/thread.h"
#include "game_maker.h"

Acceptor::Acceptor(const std::string& servname,
                   std::vector<std::unique_ptr<ClientHandler>>& clients,
                   GameMaker& game_maker):
    listener(servname.c_str()), clients(clients), game_maker(game_maker) {}

void Acceptor::run() {
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

void Acceptor::stop() {
    Thread::stop();
    listener.shutdown(CLOSE_BOTH_STREAMS);
}
