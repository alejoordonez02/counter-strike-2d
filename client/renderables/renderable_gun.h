#ifndef CLIENT_RENDERABLES_RENDERABLE_GUN_H
#define CLIENT_RENDERABLES_RENDERABLE_GUN_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/renderable_gun_effect.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/position.h"

class RenderableGun {
private:
    Position position;
    double facing_angle;
    Animation* current_animation;
    std::shared_ptr<AnimationProvider> animation_provider;
    RenderableGunEffect gun_effect;

    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    void load_animation(const std::string& animation_name);

public:
    explicit RenderableGun(
        std::shared_ptr<AnimationProvider> animation_provider);

    void update(const Position& position, const Position& aim_position,
                double facing_angle, WeaponName weapon_type, bool is_shooting);
    void render(SDL2pp::Renderer& renderer);

    void skip_frames(uint8_t frames_to_skip);
    ~RenderableGun();
};

#endif
