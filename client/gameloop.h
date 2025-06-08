#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>

#include "texture_provider.h"
#include "animation_provider.h"
#include "input_handler.h"

#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../common/network/dto.h"
#include "render.h"


class GameLoop {
    private:
        Render render;
        
        bool is_running = true;

        Queue<std::unique_ptr<DTO>>& snapshots_queue;
        Queue<std::shared_ptr<DTO>>& commands_queue;

        InputHandler input_handler;

    public:
        GameLoop(Queue<std::unique_ptr<DTO>>& snapshots, Queue<std::shared_ptr<DTO>>& commands);

        void run();

        Snapshot get_snapshot_from_queue();

        void closeWindow();
};

#endif // GAMELOOP_H