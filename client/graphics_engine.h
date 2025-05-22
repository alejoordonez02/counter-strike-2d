#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <SDL2pp/SDL2pp.hh>
#include "texture_provider.h"


class GraphicsEngine {
    private:
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
        TextureProvider texture_provider;
        
        bool is_running = true;

        


public:
    GraphicsEngine();

    void run();

    void render();

    void handleEvents();

    void closeWindow();
};

#endif // GRAPHICS_ENGINE_H