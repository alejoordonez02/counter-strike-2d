#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/network/socket/liberror.h"
#include "common/network/socket/socket.h"
#include "common/thread.h"
#include "server/client_session.h"
#include "server/game_monitor.h"

class Acceptor: public Thread {
    private:
    Socket skt;
    std::vector<std::unique_ptr<ClientSession>> clients;
    GameMonitor& gm_ref;

    public:
    Acceptor(const std::string& servname, GameMonitor& gm):
            skt(servname.c_str()), gm_ref(gm) {}

    void run() override {
        try {
            while (true) {
                Socket peer_skt = skt.accept();
                auto new_client = std::make_unique<ClientSession>(
                        std::move(peer_skt), gm_ref);
                clients.push_back(std::move(new_client));

                clear_finished_clients();
                // gm_ref.reap_dead_games();
            }
        } catch (const LibError& err) {  // cierre de server
                                         // handle_server_shutdown()
        }
    }

    void force_stop() {
        skt.shutdown(2);
        skt.close();
    }

    ~Acceptor() = default;

    private:
    void clear_finished_clients() {
        clients.erase(std::remove_if(clients.begin(), clients.end(),
                                     [](std::unique_ptr<ClientSession> c) {
                                         return c->is_finished();
                                     }),
                      clients.end());
    }
};

#endif
