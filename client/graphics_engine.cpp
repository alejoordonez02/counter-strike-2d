#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "./graphics_engine.h"



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

    SDL2pp::Texture* mira = texture_provider.get_texture();
        
    int centro_pantalla_y = renderer.GetOutputHeight() / 2;
    int centro_pantalla_x = renderer.GetOutputWidth() / 2;
    int altura = mira->GetHeight();
    int ancho = mira->GetWidth();

    renderer.Copy(
            *mira, 
            SDL2pp::Rect(ancho/2, altura/2, ancho, altura),
			SDL2pp::Rect(centro_pantalla_x/2, centro_pantalla_y/2, 50, 50)
		);

    renderer.Present();
}

void GraphicsEngine::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
}
