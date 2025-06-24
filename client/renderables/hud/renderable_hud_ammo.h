#ifndef CLIENT_RENDERABLES_RENDERABLE_HUD_AMMO_H
#define CLIENT_RENDERABLES_RENDERABLE_HUD_AMMO_H

#include <utility>

#include "common/position.h"
#include "client/providers/animation_provider.h"
#include "client/renderables/hud/renderable_numbers.h"
#include "common/network/dtos/snapshot_dto.h"

class RenderableHUDAmmo {
private:
    void update_gun_icon(WeaponName weapon_name);

    RenderableNumbers numbers;

    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    Position get_icon_position(const Position& screen_size, const Position& icon_size);
    Position get_number_position(const Position& screen_size, const Position& icon_size, int spacing);
public:
    RenderableHUDAmmo(std::shared_ptr<AnimationProvider> animation_provider);

    void update(const PrivateWeaponDTO& weapon_data);
    
    void render(SDL2pp::Renderer& renderer);
};

#endif
