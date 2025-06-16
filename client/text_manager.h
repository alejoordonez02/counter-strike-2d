#ifndef CLIENT_TEXT_MANAGER_H
#define CLIENT_TEXT_MANAGER_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Renderer.hh>

#include "common/snapshot.h"

class TextManager {
    private:
    SDL2pp::SDLTTF sdl_ttf;     // inicializar fuentes
    SDL2pp::Font font;

    bool show_text;
    Snapshot snapshot;

    public:
    TextManager();

    void update(const Snapshot& snapshot);

    void render(SDL2pp::Renderer& renderer);

    void show_terrorist_won(SDL2pp::Renderer& renderer);
};

#endif
