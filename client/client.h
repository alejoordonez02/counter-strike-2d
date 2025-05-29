#ifndef CLIENT_H
#define CLIENT_H

// #include "common/player_commands.h"
// #include "common/event.h"
// #include "common/receiver.h"
// #include "common/sender.h"
#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../common/player_commands/command.h"
// #include "input_handler.h"

class Client {
private:
    // InputHandler input_handler;
    Queue<Snapshot> snapshots;
    Queue<PlayerDTO> comandos;

    // Sender sender;
    // Receiver receiver;

public:
    void run();
};

#endif
