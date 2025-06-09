#ifndef SERVER_CLIENT_SETUP_H
#define SERVER_CLIENT_SETUP_H

#include "common/network/connection.h"
#include "common/thread.h"
#include "server/game_monitor.h"
#include "server/model/player.h"

class ClientSetup: public Thread {
    // pequeño thread sincronico con cliente para manejar lobby (create y join),
    // nace y muere antes que los senders y receivers
    private:
    Connection& con;
    GameMonitor& gm;
    Player& return_p;

    public:
    ClientSetup(Connection& c, GameMonitor& gm, Player& p):
            con(c), gm(gm), return_p(p) {}

    void run() override {}

    ~ClientSetup() = default;
};

#endif
