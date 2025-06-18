#ifndef CLIENT_RENDERABLES_RENDERABLE_HUD_MONEY_H
#define CLIENT_RENDERABLES_RENDERABLE_HUD_MONEY_H

#include "client/renderables/hud/renderable_hud_base.h"

class RenderableHUDMoney : public RenderableHUDBase {
public:
    RenderableHUDMoney(std::shared_ptr<AnimationProvider> animation_provider);
    std::string get_icon_name() const override;
    SDL2pp::Point get_icon_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size) const override;
    SDL2pp::Point get_number_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size, int spacing) const override;
};

#endif
