#include "client/renderables/hud/renderable_hud_timer.h"

#include "client/animation_provider.h"

#include <utility>
#include "renderable_numbers.h"

RenderableHUDTimer::RenderableHUDTimer(
        std::shared_ptr<AnimationProvider> animation_provider)
    : RenderableHUDBase(animation_provider) {
    icon_animation = std::move(animation_provider->make_animation(get_icon_name()));
}

std::string RenderableHUDTimer::get_icon_name() const {
    return "clock";
}

SDL2pp::Point RenderableHUDTimer::get_icon_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size) const {
    int spacing_between = icon_size.x / 4;
    // centrado horizontal, abajo
    int x = (screen_size.x - icon_size.x) / 2;
    int y = screen_size.y - icon_size.y - spacing_between;
    return SDL2pp::Point(x, y);
}

SDL2pp::Point RenderableHUDTimer::get_number_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size, int spacing) const {
    SDL2pp::Point icon_pos = get_icon_position(screen_size, icon_size);
    // pos calculada anteriormente + tamaño del icono + padding entre icono y numero
    return SDL2pp::Point(icon_pos.x + icon_size.x + spacing, icon_pos.y);
}

