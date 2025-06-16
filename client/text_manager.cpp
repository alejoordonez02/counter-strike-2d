#include "client/text_manager.h"

#include <utility>

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

TextManager::TextManager():
        font(DATA_PATH "/assets/gfx/fonts/sourcesans.ttf", 16) {
}

void TextManager::show_terrorist_won(SDL2pp::Renderer& renderer) {
    // texturas
    SDL2pp::Surface text_surface = font.RenderText_Blended("Terrorists win the Round", SDL_Color{255,255,255,255});
    SDL2pp::Texture text_texture(renderer, text_surface);

    SDL2pp::Point punto = renderer.GetOutputSize();
    int text_w = text_texture.GetWidth();
    int text_h = text_texture.GetHeight();
    SDL2pp::Rect dst((punto.x - text_w)/2, (punto.y - text_h)/2, text_w, text_h);
    renderer.Copy(text_texture, SDL2pp::NullOpt, dst);
}
