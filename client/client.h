#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <memory>
#include <string>

#include "client/input_handler.h"
#include "common/network/receiver.h"
#include "common/network/sender.h"
#include "common/queue.h"

class Client {
private:
    Connection con;

    Queue<std::unique_ptr<DTO>> commands;
    Queue<std::unique_ptr<DTO>> snapshots;

    Sender sender;
    Receiver receiver;
    InputHandler input_handler;

public:
    Client(const std::string& hostname, const std::string& servname);
    void run(int use_id);
};

#endif
