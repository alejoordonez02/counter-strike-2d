#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "graphics_engine.h"
#include <unistd.h>
#include "pointer.h"


const static int RATE = 1000/60;


GraphicsEngine::GraphicsEngine(): 
    sdl(SDL_INIT_VIDEO),
    window("Mi ventana SDL2pp",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    texture_provider(renderer){
        // poner color de fondo rojo
        renderer.SetDrawColor(255, 0, 0, 255);
        
}


void GraphicsEngine::run(){
    SDL2pp::Texture* pointer = texture_provider.get_texture_pointer();
    SDL2pp::Texture* terrorista_texture = texture_provider.get_texture_terrorist();
    
    Player player(*terrorista_texture);
    Pointer pointer(*pointer);
    
    while (is_running) {
        uint32_t t1 = SDL_GetTicks();

        is_running = handleEvents(player);
        
        update(player, RATE);
        
        render(player);

        // sleep_or_catch_up(t1);
        usleep(FRAME_RATE);
    }
}




void GraphicsEngine::render(Player &player){
    // renderer.SetDrawColor(0x80, 0x80, 0x80);

    // limpiar la ventana
    renderer.Clear();

    player.render(renderer);

    // mostrar la ventana
    renderer.Present();
}


void GraphicsEngine::update(Player &player, float delta_time){
    player.update(delta_time);
}

void GraphicsEngine::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}






/**
 * Va a tomar un evento de teclado, y actualizará el modelo en función de los eventos que lleguen.
 * En un juego real no se tomará de a un evento por vuelta del gameloop, sino que se deberán tomar TODOS
 * o N eventos por vuelta
 */
bool GraphicsEngine::handleEvents(Player &player) {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?    
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
            case SDL_MOUSEMOTION:
                std::cout << "Oh! Mouse" << std::endl;
                break;
            case SDL_QUIT:
                std::cout << "Cerrando ventana..." << std::endl;
                return false;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
    return true;
}



void GraphicsEngine::sleep_or_catch_up(uint32_t& t1) {
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
