#ifndef CLIENT_TEXT_MANAGER_H
#define CLIENT_TEXT_MANAGER_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Renderer.hh>

#include "common/snapshot.h"
#include "client/renderables/hud/renderable_numbers.h"

class TextManager {
    private:
    SDL2pp::SDLTTF sdl_ttf;     // inicializar fuentes
    SDL2pp::Font font;

    bool show_text;
    Snapshot snapshot;

    RenderableNumbers hp_numbers;
    RenderableNumbers timer_numbers;
    RenderableNumbers money_numbers;


    public:
    TextManager(std::shared_ptr<AnimationProvider> animation_provider);

    void load_data();

    void update(const Snapshot& snapshot);

    void render(SDL2pp::Renderer& renderer);

    void show_terrorist_won(SDL2pp::Renderer& renderer);
};

#endif
