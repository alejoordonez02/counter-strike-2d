#ifndef CLIENT_HUD_MANAGER_H
#define CLIENT_HUD_MANAGER_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Renderer.hh>

#include "common/network/dtos/snapshot_dto.h"
#include "client/renderables/hud/renderable_hud_health.h"
#include "client/renderables/hud/renderable_hud_timer.h"
#include "client/renderables/hud/renderable_hud_money.h"
#include "client/renderables/renderable_pointer.h"

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

    RenderablePointer pointer;

    void calculate_fps(uint32_t& fps_timer);
    void show_fps(SDL2pp::Renderer& renderer);


    public:
    HUDManager(std::shared_ptr<AnimationProvider> animation_provider);

    void update(const SnapshotDTO& snapshot, uint32_t& fps_timer);

    bool get_user_is_shooting(const SnapshotDTO& snapshot);

    void render(SDL2pp::Renderer& renderer);

    void show_terrorist_won(SDL2pp::Renderer& renderer);

    
};

#endif
