#include "hud_manager.h"

#include <utility>

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>

HUDManager::HUDManager(std::shared_ptr<AnimationProvider> animation_provider):
        font(DATA_PATH "/assets/gfx/fonts/sourcesans.ttf", 16),
        show_text(false),
        hud_hp(animation_provider)
        // hud_timer(animation_provider),
        // hud_money(animation_provider)
         {
}


void HUDManager::load_data() {
    hud_hp.initialize_data();
    // hud_timer.load_icons();
    // hud_money.load_icons();
}


void HUDManager::update(const Snapshot& snapshot) {
    this->snapshot = snapshot;
    show_text = snapshot.round_number >= 50 ? true : false;

    // hp = snapshot.players[0].hp;

    uint8_t hp = 98;
    hud_hp.update(hp);
    // hud_timer.update(snapshot.time);
    // hud_money.update(snapshot.your_player.total_money);

}


void HUDManager::render(SDL2pp::Renderer& renderer) {
    hud_hp.render(renderer);

    if(!show_text){
        return;
    }

    show_terrorist_won(renderer);

}



void HUDManager::show_terrorist_won(SDL2pp::Renderer& renderer) {
    // texto en color blanco
    SDL2pp::Surface text_surface = font.RenderText_Blended("Terrorists win the Round", SDL_Color{255,255,255,255});
    // convertir texto en textura para poder dibujarla
    SDL2pp::Texture text_texture(renderer, text_surface);
    
    SDL2pp::Point punto = renderer.GetOutputSize();
    int text_w = text_texture.GetWidth();
    int text_h = text_texture.GetHeight();
    
    int padding = 20;
    SDL2pp::Rect dst((punto.x - text_w)/2, (punto.y - text_h)/3, text_w, text_h);
    // recuadro transparente detrás del texto
    SDL2pp::Rect box(dst.x - padding/2, dst.y - padding/3, dst.w + padding, dst.h + padding);

    renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);     // permitir transparencia
    renderer.SetDrawColor(0, 0, 0, 128); // 128 = 50% transparencia
    renderer.FillRect(box);

    // texto encima
    renderer.Copy(text_texture, SDL2pp::NullOpt, dst);
}
