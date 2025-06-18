#ifndef CLIENT_RENDERABLES_RENDERABLE_HUD_HEALTH_H
#define CLIENT_RENDERABLES_RENDERABLE_HUD_HEALTH_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Point.hh"
#include "SDL2pp/Renderer.hh"
#include "client/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/hud/renderable_numbers.h"

class RenderableHUDHealth {
    private:

    std::shared_ptr<AnimationProvider> animation_provider;
    std::unique_ptr<Animation> heart_icon_animation;
    RenderableNumbers heart_numbers;

    public:
    RenderableHUDHealth(std::shared_ptr<AnimationProvider> animation_provider);

    void update(uint8_t number);

    void render(SDL2pp::Renderer& renderer);

    ~RenderableHUDHealth();
};

#endif
