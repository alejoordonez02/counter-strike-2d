#ifndef CLIENT_RENDERABLES_RENDERABLE_LEGS_H
#define CLIENT_RENDERABLES_RENDERABLE_LEGS_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"
#include "common/position.h"

class RenderableLegs {
    private:
    Position position;
    double facing_angle;

    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    std::shared_ptr<AnimationProvider> animation_provider;

    void load_animation(const std::string& animation_name);

    public:
    explicit RenderableLegs(
            std::shared_ptr<AnimationProvider> animation_provider);

    void update(const Position& position, double facing_angle, bool is_walking);
    void render(SDL2pp::Renderer& renderer);

    void skip_frames(uint8_t frames_to_skip);
    ~RenderableLegs();
};

#endif
