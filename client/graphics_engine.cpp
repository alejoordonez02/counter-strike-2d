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
        uint32_t t1 = SDL_GetTicks();

        handleEvents();
        
        render();

        update();

        sleep_or_catch_up(t1);
    }
}

int frame_index = 0;
int terrorista_src = 0;
int terrorista_pos_x = 0;

const static int RATE = 1000/60;



void GraphicsEngine::render(){
   
    // limpiar la ventana
    renderer.Clear();

    SDL2pp::Texture* pointer = texture_provider.get_texture_pointer();

    SDL2pp::Texture* terrorista = texture_provider.get_texture_terrorist();
    
    int centro_pantalla_y = renderer.GetOutputHeight() / 2;
    int centro_pantalla_x = renderer.GetOutputWidth() / 2;
    int h_pointer = pointer->GetHeight();
    int w_pointer = pointer->GetWidth();

    renderer.Copy(
            *pointer, 
            SDL2pp::Rect(w_pointer/2, h_pointer/2, w_pointer, h_pointer),
			SDL2pp::Rect(centro_pantalla_x/2, centro_pantalla_y/2, w_pointer, h_pointer)
		);
    
    renderer.Copy(
        *terrorista, 
        SDL2pp::Rect(terrorista_src, 0, 32, 32),
        SDL2pp::Rect(terrorista_pos_x, 0, 32, 32),
        90
    );

    // mostrar la ventana
    renderer.Present();
}


void GraphicsEngine::update(){
    frame_index += 1;
    terrorista_src = (frame_index % 2) * 32;
    terrorista_pos_x += 1;
}

void GraphicsEngine::closeWindow() {
    this->window.~Window(); 
    this->renderer.~Renderer();
    this->sdl.~SDL();
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

