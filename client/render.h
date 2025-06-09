#ifndef RENDER_H
#define RENDER_H

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include <memory>

#include "texture_provider.h"
#include "animation_provider.h"
#include "input_handler.h"
#include "../common/queue.h"
#include "../common/snapshot.h"
#include "../server/player_commands/command.h"
#include "renderables/renderable_player.h"
#include "../common/snapshot.h"


class Render {
    private:
        SDL2pp::SDL sdl;
        SDL2pp::Window window;
        SDL2pp::Renderer renderer;
        
        std::unordered_map<uint16_t, std::unique_ptr<RenderablePlayer>> players_renderables;

        std::shared_ptr<AnimationProvider> animation_provider;


public:
    Render();

    void run();

    void update(Snapshot snapshot);

    void render();

    void closeWindow();
};

#endif // Render_H