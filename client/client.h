#ifndef CLIENT_H
#define CLIENT_H

#include "common/player_commands.h"
#include "common/event.h"
#include "common/queue.h"
#include "common/receiver.h"
#include "common/sender.h"

#include "input_handler.h"

class Client {
private:
    InputHandler input_handler;
    Queue<std::unique_ptr<Event>> events;
    Queue<Command> cmds;
    Sender sender;
    Receiver receiver;

public:
    void run();
};

#endif
