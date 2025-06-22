#ifndef CLIENT_HUD_MANAGER_H
#define CLIENT_HUD_MANAGER_H

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Renderer.hh>

#include "common/network/dtos/snapshot_dto.h"
#include "client/renderables/hud/renderable_hud_health.h"
#include "client/renderables/hud/renderable_hud_timer.h"
#include "client/renderables/hud/renderable_hud_money.h"

class HUDManager {
    private:
    SDL2pp::SDLTTF sdl_ttf;     // inicializar fuentes
    SDL2pp::Font font;

    bool show_text;
    SnapshotDTO snapshot;

    RenderableHUDHealth hud_hp;
    RenderableHUDTimer hud_timer;
    RenderableHUDMoney hud_money;


    public:
    HUDManager(std::shared_ptr<AnimationProvider> animation_provider);

    void update(const SnapshotDTO& snapshot);

    void render(SDL2pp::Renderer& renderer);

    void show_terrorist_won(SDL2pp::Renderer& renderer);
};

#endif
