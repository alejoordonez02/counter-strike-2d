#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "common/network/socket/socket.h"
#include "common/network/socket/liberror.h"
#include "common/thread.h"
#include "client_session.h"
#include "game_monitor.h"

class Acceptor: public Thread {
private:
    Socket skt;
    GameMonitor& gm_ref;
    std::vector<ClientSession> clients;

public:
    Acceptor(const std::string& servname, GameMonitor& gm): skt(servname.c_str()), gm_ref(gm) {}

    void run() override {
        try {
            while (true) {
                Socket peer_skt = skt.accept();
                ClientSession new_client(std::move(peer_skt), gm_ref);
                new_client.start_lobby_phase();
                clients.push_back(std::move(new_client));

                clear_offline_clients();
                gm_ref.reap_dead_games();
            }
        } catch (const LibError& err) {  // cierre de server
            gm_ref.shutdown(); // (metodo de GameMonitor con mutex, dejarlo cerrado/bloqueado al final al GM)
            terminate_all_clients();
        }
    }
    
    void force_stop() {
        skt.shutdown(2);
        skt.close();
    }
    
    ~Acceptor() = default;

private:
    void clear_offline_clients() {
        clients.erase(std::remove_if(clients.begin(), clients.end(),
                                     [](ClientSession& c) {
                                        if (c.is_offline()) {
                                            c.end_lobby_phase();
                                            return true;
                                        }
                                        return false;
                                     }),
                      clients.end());
    }

    void terminate_all_clients() {
        for (auto& c : clients) {
            c.force_terminate();
        }
        clients.clear();
    }
};

#endif
