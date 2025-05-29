#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <SDL2pp/SDL2pp.hh>
#include "texture_provider.h"
#include "player.h"
#include "pointer.h"


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

    void render(Player &player, Pointer &pointer);

    void update(Player &player, Pointer &pointer, float delta_time);

    bool handleEvents(Player &player);

    void sleep_or_catch_up(uint32_t& t1);

    void closeWindow();
};

#endif // GRAPHICS_ENGINE_H