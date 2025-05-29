#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL2pp/SDL2pp.hh>

#include "texture_provider.h"
#include "jugador.h"
#include "pointer.h"
#include "input_handler.h"

#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../common/player_commands/command.h"


class GameLoop {
    private:
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
        TextureProvider texture_provider;
        
        bool is_running = true;

        Queue<Snapshot>& snapshots_queue;
        Queue<PlayerDTO>& comandos_queue;

        InputHandler input_handler;

        


public:
    GameLoop(Queue<Snapshot>& snapshots, Queue<PlayerDTO>& comandos);

    void run();

    void render(Jugador &player, Pointer &pointer);

    void update(Jugador &player, Pointer &pointer, float delta_time);

    void sleep_or_catch_up(uint32_t& t1);

    void debug_simulacion_servidor(Snapshot& snapshot);

    void closeWindow();
};

#endif // GAMELOOP_H