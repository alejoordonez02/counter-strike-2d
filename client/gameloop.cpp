#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "gameloop.h"
#include <unistd.h>
#include "pointer.h"
#include "../common/player_commands/command.h"

#include "mock_server.h"

const static int RATE = 1000/60;


GameLoop::GameLoop(Queue<Snapshot>& snapshots, Queue<Command>& comandos): 
    sdl(SDL_INIT_VIDEO),
    window("Counter Strike 2D",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    texture_provider(renderer),
    snapshots_queue(snapshots),
    input_handler(comandos)
    {
        // poner color de fondo negro
        renderer.SetDrawColor(0, 0, 0, 0);
        
}


void GameLoop::run(){
    SDL2pp::Texture* pointer_texture = texture_provider.get_texture_pointer();
    SDL2pp::Texture* terrorista_texture = texture_provider.get_texture_terrorist();
    
    Jugador player(*terrorista_texture);
    Pointer pointer(*pointer_texture);

    Snapshot last_snapshot;

    mock_server(snapshots_queue);
    
    while (is_running) {
        uint32_t t1 = SDL_GetTicks();

        // TODO: asegurarse de obtener el último evento (vaciar la queue entera?)
        snapshots_queue.try_pop(last_snapshot);
        
        if(!last_snapshot.players.empty()){   
            // imprimir posicion jugador obtenido del vector de jugadores
            PlayerDTO jugador = last_snapshot.players.at(0);
            std::cout << jugador.x << std::endl;
        }

        is_running = input_handler.handle_events(player);
        
        update(player, pointer, RATE);
        
        render(player, pointer);

        // sleep_or_catch_up(t1);
        usleep(FRAME_RATE);
    }
}




void GameLoop::render(Jugador &player, Pointer &pointer){
    // renderer.SetDrawColor(0x80, 0x80, 0x80);

    // limpiar la ventana
    renderer.Clear();

    player.render(renderer);
    pointer.render(renderer);

    // mostrar la ventana
    renderer.Present();
}


void GameLoop::update(Jugador &player, Pointer &pointer, float delta_time){
    player.update(delta_time);
    pointer.update();
}

void GameLoop::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}






void GameLoop::sleep_or_catch_up(uint32_t& t1) {
    uint32_t t2 = SDL_GetTicks();

    int rest = RATE - (t2 - t1);
    if (rest < 0) {
        int behind = -rest;
        int lost = behind - behind % RATE;

        // recuperamos los frames perdidos
        uint8_t frames_to_skip = int(lost / RATE);

        // TODO: skipear frames


        t1 += lost;
    } else {
        SDL_Delay(rest);
    }

    t1 = SDL_GetTicks();
}
