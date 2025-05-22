#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "./graphics_engine.h"
#include "graphics_engine.h"


GraphicsEngine::GraphicsEngine(): 
    sdl(SDL_INIT_VIDEO),
    window("Mi ventana SDL2pp",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN),
    renderer(window, -1, SDL_RENDERER_ACCELERATED){
        // poner color de fondo rojo
        renderer.SetDrawColor(255, 0, 0, 255);
}

void GraphicsEngine::handleEvents() {
    SDL_Event event;
    
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false;
            std::cout << "Cerrando ventana..." << std::endl;
        }

    }

}

void GraphicsEngine::run(){

    while (is_running) {

        handleEvents();
        
        render();
    }
}


void GraphicsEngine::render(){
   
    // limpiar la ventana
    renderer.Clear();
    // mostrar la ventana
    renderer.Present();
}

void GraphicsEngine::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}
