#include "client/renderables/hud/renderable_hud_timer.h"

#include "client/providers/animation_provider.h"

#include <utility>
#include "renderable_numbers.h"

RenderableHUDTimer::RenderableHUDTimer(
        std::shared_ptr<AnimationProvider> animation_provider)
    : RenderableHUDBase(animation_provider) {
    icon_animation = animation_provider->make_animation(get_icon_name());
}

std::string RenderableHUDTimer::get_icon_name() const {
    return "clock";
}

Position RenderableHUDTimer::get_icon_position(const Position& screen_size, const Position& icon_size) const {
    int spacing_between = icon_size.x / 4;
    // centrado horizontal, abajo
    int x = (screen_size.x - icon_size.x) / 2;
    int y = screen_size.y - icon_size.y - spacing_between;
    return Position(x, y);
}

Position RenderableHUDTimer::get_number_position(const Position& screen_size, const Position& icon_size, int spacing) const {
    Position icon_pos = get_icon_position(screen_size, icon_size);
    // pos calculada anteriormente + tamaño del icono + padding entre icono y numero
    return Position(icon_pos.x + icon_size.x + spacing, icon_pos.y);
}

