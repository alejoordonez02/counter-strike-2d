#ifndef CLIENT_RENDERABLES_RENDERABLE_LEGS_H
#define CLIENT_RENDERABLES_RENDERABLE_LEGS_H

#include <memory>
#include <string>
#include <unordered_map>

#include "client/animation_provider.h"
#include "client/renderables/animation.h"

class RenderableLegs {
    private:
    SDL2pp::Point position;
    double facing_angle;

    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    std::shared_ptr<AnimationProvider> animation_provider;

    public:
    explicit RenderableLegs(
            std::shared_ptr<AnimationProvider> animation_provider);

    void update(const SDL2pp::Point& position, double facing_angle);
    void render(SDL2pp::Renderer& renderer);

    void load_animation(const std::string& animation_name);
    ~RenderableLegs();
};

#endif
