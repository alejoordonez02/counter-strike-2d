#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL2pp/SDL2pp.hh>

#include "texture_provider.h"
#include "input_handler.h"

#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../common/player_commands/command.h"
#include "renderables/renderable_player.h"


class GameLoop {
    private:
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
        // TextureProvider texture_provider;
        
        bool is_running = true;

        Queue<Snapshot>& snapshots_queue;
        Queue<PlayerDTO>& comandos_queue;

        InputHandler input_handler;
        Snapshot ultima_snapshot;
        
        // encapsular luego en una clase renderables?
        std::unordered_map<uint32_t, std::unique_ptr<RenderablePlayer>> players_renderables;



public:
    GameLoop(Queue<Snapshot>& snapshots, Queue<PlayerDTO>& comandos);

    void run();

    void update_renderables_from_snapshot();

    void render_all();


    void sleep_or_catch_up(uint32_t& t1);

    void _debug_simulacion_servidor(Snapshot& snapshot);

    void closeWindow();
};

#endif // GAMELOOP_H