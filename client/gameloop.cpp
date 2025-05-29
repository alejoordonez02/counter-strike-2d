#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "gameloop.h"
#include <unistd.h>
#include "pointer.h"


const static int RATE = 1000/60;


GameLoop::GameLoop(Queue<Snapshot>& snapshots, Queue<PlayerDTO>& comandos): 
    sdl(SDL_INIT_VIDEO),
    window("Counter Strike 2D",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    texture_provider(renderer),
    snapshots_queue(snapshots),
    comandos_queue(comandos)
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
    
    while (is_running) {
        uint32_t t1 = SDL_GetTicks();

        while (snapshots_queue.try_pop(last_snapshot)) {}

        // imprimir posicion jugador obtenido del vector de jugadores
        PlayerDTO jugador = last_snapshot.players.at(0);
        std::cout << jugador.x << std::endl;

        is_running = handleEvents(player);
        
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






bool GameLoop::handleEvents(Jugador &player) {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        player.moveRigth();
                        break;
                    case SDLK_UP:
                        player.moveUp();
                        break;
                    case SDLK_DOWN:
                        player.moveDown();
                        break;
                    }
                } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        player.stopMoving();
                        break;
                    case SDLK_UP:
                        player.stopMoving();
                        break;
                    case SDLK_DOWN:
                        player.stopMoving();
                        break;
                    } 
                }// Fin KEY_UP
                break;
            // case SDL_MOUSEMOTION:
                // std::cout << "Oh! Mouse" << std::endl;
                // break;
            case SDL_QUIT:
                std::cout << "Cerrando ventana..." << std::endl;
                return false;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
    return true;
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
