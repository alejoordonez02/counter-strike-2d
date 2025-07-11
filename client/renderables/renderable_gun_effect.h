#ifndef CLIENT_RENDERABLES_RENDERABLE_GUN_EFFECT_H
#define CLIENT_RENDERABLES_RENDERABLE_GUN_EFFECT_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/position.h"
#include "client/camera.h"

class RenderableGunEffect {
private:
    Position position;
    Position gun_position;
    Position aim_position;
    double facing_angle;

    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    std::shared_ptr<AnimationProvider> animation_provider;

    void load_animation(const std::string& animation_name);

public:
    explicit RenderableGunEffect(
        std::shared_ptr<AnimationProvider> animation_provider);

    void update(const Position& player_position, const Position& gun_position,
                const Position& aim_position, double facing_angle,
                WeaponName weapon_type, bool is_shooting);
    void render_line(SDL2pp::Renderer& renderer);
    void render(SDL2pp::Renderer& renderer);

    void skip_frames(uint8_t frames_to_skip);
    ~RenderableGunEffect();
};

#endif
