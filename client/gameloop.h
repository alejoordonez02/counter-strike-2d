#ifndef CLIENT_GAMELOOP_H
#define CLIENT_GAMELOOP_H

#include <memory>

#include "client/input_handler.h"
#include "client/render.h"
#include "common/network/dto.h"
#include "common/queue.h"
#include "common/snapshot.h"

class GameLoop {
    private:
    Render render;

    bool is_running = true;

    Queue<std::unique_ptr<DTO>>& snapshots_queue;
    Queue<std::shared_ptr<DTO>>& commands_queue;

    InputHandler input_handler;

    public:
    GameLoop(Queue<std::unique_ptr<DTO>>& snapshots,
             Queue<std::shared_ptr<DTO>>& commands);

    void run();

    Snapshot get_snapshot_from_queue(Snapshot last_snapshot);

    void closeWindow();
};

#endif  // GAMELOOP_H
