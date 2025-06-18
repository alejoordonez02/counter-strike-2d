#ifndef CLIENT_RENDERABLES_RENDERABLE_HUD_TIMER_H
#define CLIENT_RENDERABLES_RENDERABLE_HUD_TIMER_H

#include "client/renderables/hud/renderable_hud_base.h"

class RenderableHUDTimer : public RenderableHUDBase {
public:
    RenderableHUDTimer(std::shared_ptr<AnimationProvider> animation_provider);
    std::string get_icon_name() const override;
    SDL2pp::Point get_icon_position(const SDL2pp::Renderer& renderer, const SDL2pp::Point& icon_size) const override;
    SDL2pp::Point get_number_position(const SDL2pp::Renderer& renderer, const SDL2pp::Point& icon_size, int spacing) const override;
};

#endif
