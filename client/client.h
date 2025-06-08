#ifndef CLIENT_H
#define CLIENT_H

#include "../common/network/receiver.h"
#include "../common/network/sender.h"
#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../server/player_commands/command.h"
#include "input_handler.h"

class Client {
private:
    Connection con;
    
    Queue<std::shared_ptr<DTO>> commands;
    Queue<std::unique_ptr<DTO>> snapshots;
    
    Sender sender;
    Receiver receiver;
    InputHandler input_handler;

public:
    Client(const std::string& hostname, const std::string& servname);
    void run();
};

#endif
