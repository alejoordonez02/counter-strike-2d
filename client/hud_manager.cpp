#include "hud_manager.h"

#include <utility>

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <algorithm>

HUDManager::HUDManager(std::shared_ptr<AnimationProvider> animation_provider):
        font(DATA_PATH "/assets/gfx/fonts/sourcesans.ttf", 16),
        show_text(false),
        hud_hp(animation_provider),
        hud_timer(animation_provider),
        hud_money(animation_provider),
        pointer(animation_provider)
         {
}


void HUDManager::update(const Snapshot& snapshot, uint32_t& fps_timer) {
    this->snapshot = snapshot;
    show_text = snapshot.round_number >= 50 ? true : false;

    int time = snapshot.time_left; //60 * 5;
    std::string time_string = std::to_string(time / 60) + ":" + (time % 60 < 10 ? "0" : "") + std::to_string(time % 60);

    // update hud elements
    hud_timer.update(time_string);
    hud_hp.update(snapshot.user_data.player_hp);
    hud_money.update(snapshot.user_data.total_money);

    // pointer
    int user_id = snapshot.user_data.player_id;
    // buscar el jugador por id en el vector
    auto it = std::find_if(snapshot.players.begin(), snapshot.players.end(),
        [user_id](const PlayerData& p) { return p.player_id == user_id; });
    if (it == snapshot.players.end()) {
        // si no existe, no actualizamos el puntero
        return;
    }

    bool user_is_attacking = get_user_is_shooting(snapshot);
    pointer.update(user_is_attacking);

    // fps counter
    calculate_fps(fps_timer);
}

bool HUDManager::get_user_is_shooting(const Snapshot& snapshot) {
    // busca el jugador actual en el snapshot 
    // para obtener su estado de is_shooting
    int user_id = snapshot.user_data.player_id;
    auto it = std::find_if(snapshot.players.begin(), snapshot.players.end(),
        [user_id](const PlayerData& p) { return p.player_id == user_id; });
    if (it != snapshot.players.end()) {
        return it->is_shooting;
    }
    // Si no se encuentra, devolver false
    return false;
}


void HUDManager::render(SDL2pp::Renderer& renderer) {
    pointer.render(renderer);
    
    hud_hp.render(renderer);
    hud_timer.render(renderer);
    hud_money.render(renderer);
    

    if(show_text){
        show_terrorist_won(renderer);
    }

    show_fps(renderer);
}

void HUDManager::show_fps(SDL2pp::Renderer& renderer) {
    // mostrar fps en la esquina superior izquierda
    std::string last_fps_string = "FPS: " + std::to_string(last_fps);
    SDL2pp::Surface text_surface = font.RenderText_Blended(last_fps_string, SDL_Color{255,255,255,255});
    SDL2pp::Texture text_texture(renderer, text_surface);

    int text_w = text_texture.GetWidth();
    int text_h = text_texture.GetHeight();
    int padding = 10;

    SDL2pp::Rect dst(padding, padding, text_w, text_h);
    // SDL2pp::Rect box(dst.x - padding/2, dst.y - padding/3, dst.w + padding, dst.h + padding);

    renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer.SetDrawColor(0, 0, 0, 128); // fondo semitransparente
    // renderer.FillRect(box);

    renderer.Copy(text_texture, SDL2pp::NullOpt, dst);
}


void HUDManager::calculate_fps(uint32_t& fps_timer) {
    frame_count++;  // contar frame renderizado

    uint32_t now = SDL_GetTicks();
    // si pasó 1 segundo imprime los frames y resetea contador
    if (now - fps_timer >= 1000) {
        last_fps = frame_count;
        frame_count = 0;
        fps_timer = now;
    }
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
