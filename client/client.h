#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <memory>
#include <string>

#include "client/input_handler.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/map_name.h"
#include "common/queue.h"

class Client {
private:
    Connection con;

    Queue<std::shared_ptr<DTO>> commands;
    Queue<std::unique_ptr<DTO>> snapshots;

    Sender sender;
    Receiver receiver;
    InputHandler input_handler;

    MapName lobby_phase(
        int i = 0);  // i != 0 no abre la interfaz de lobby (para testear)

public:
    Client(const std::string& hostname, const std::string& servname);
    void run(int i = 0);  // igual a arriba
};

#endif
