#include "client/text_manager.h"

#include <utility>

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>

TextManager::TextManager():
        font(DATA_PATH "/assets/gfx/fonts/sourcesans.ttf", 16),
        show_text(false) {
}


void TextManager::update(const Snapshot& snapshot) {
    this->snapshot = snapshot;

    std::cout << "show_text: " << snapshot.round_number << std::endl;
    show_text = snapshot.round_number >= 10 ? true : false;

}


void TextManager::render(SDL2pp::Renderer& renderer) {
    if(!show_text){
        return;
    }

    show_terrorist_won(renderer);

}



void TextManager::show_terrorist_won(SDL2pp::Renderer& renderer) {
    SDL2pp::Surface text_surface = font.RenderText_Blended("Terrorists win the Round", SDL_Color{255,255,255,255});
    SDL2pp::Texture text_texture(renderer, text_surface);
    
    SDL2pp::Point punto = renderer.GetOutputSize();
    int text_w = text_texture.GetWidth();
    int text_h = text_texture.GetHeight();
    SDL2pp::Rect dst((punto.x - text_w)/2, (punto.y - text_h)/2, text_w, text_h);
    renderer.Copy(text_texture, SDL2pp::NullOpt, dst);
}
