#ifndef CLIENT_HUD_MANAGER_H
#define CLIENT_HUD_MANAGER_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>

#include <utility>
#include <algorithm>

#include "common/network/dtos/snapshot_dto.h"
#include "client/renderables/hud/renderable_hud_health.h"
#include "client/renderables/hud/renderable_hud_timer.h"
#include "client/renderables/hud/renderable_hud_money.h"
#include "client/renderables/hud/renderable_hud_total_ammo.h"
#include "client/renderables/hud/renderable_hud_loaded_ammo.h"
#include "client/renderables/hud/renderable_hud_buy_guns.h"
#include "client/renderables/renderable_pointer.h"
#include "client/game_config.h"

class HUDManager {
    private:
    SDL2pp::SDLTTF sdl_ttf;     // inicializar fuentes
    SDL2pp::Font font;

    bool show_text;
    
    // fps
    int frame_count = 0;
    int last_fps = 0;

    RenderableHUDHealth hud_hp;
    RenderableHUDTimer hud_timer;
    RenderableHUDMoney hud_money;
    RenderableHUDTotalAmmo hud_total_ammo;
    RenderableHUDLoadedAmmo hud_loaded_ammo;
    RenderableHUDBuyGuns hud_buy_guns;

    RenderablePointer pointer;

    void calculate_fps(uint32_t& fps_timer);
    void show_fps(SDL2pp::Renderer& renderer);


    public:
    HUDManager(std::shared_ptr<AnimationProvider> animation_provider, const GameConfig& game_config);

    void update(const SnapshotDTO& snapshot, PrivatePlayerDTO& user_data,
        uint32_t& fps_timer);

    bool get_user_is_shooting(const SnapshotDTO& snapshot,
        PrivatePlayerDTO& user_data);

    void render(SDL2pp::Renderer& renderer);

    void show_terrorist_won(SDL2pp::Renderer& renderer);
    
    // Métodos para controlar el menú de compra
    void show_buy_menu() { hud_buy_guns.show(); }
    void hide_buy_menu() { hud_buy_guns.hide(); }
    bool is_buy_menu_visible() const { return hud_buy_guns.is_visible(); }

    
};

#endif
