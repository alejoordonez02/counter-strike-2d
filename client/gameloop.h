#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>

#include "texture_provider.h"
#include "animation_provider.h"
#include "input_handler.h"

#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../server/player_commands/command.h"
#include "renderables/renderable_player.h"
#include "render.h"


class GameLoop {
    private:
        Render render;
        
        bool is_running = true;

        Queue<Snapshot>& snapshots_queue;
        Queue<PlayerDTO>& comands_queue;

        InputHandler input_handler;
        Snapshot ultima_snapshot;
        

public:
    GameLoop(Queue<Snapshot>& snapshots, Queue<PlayerDTO>& comandos);

    void run();

    void update_renderables_from_snapshot();

    void render_all();

    void closeWindow();
};

#endif // GAMELOOP_H