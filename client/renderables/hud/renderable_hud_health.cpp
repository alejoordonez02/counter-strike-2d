#include "client/renderables/hud/renderable_hud_health.h"

RenderableHUDHealth::RenderableHUDHealth(std::shared_ptr<AnimationProvider> animation_provider)
    : RenderableHUDBase(animation_provider) {
    icon_animation = animation_provider->make_animation(get_icon_name());
}

std::string RenderableHUDHealth::get_icon_name() const {
    return "heart";
}

SDL2pp::Point RenderableHUDHealth::get_icon_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size) const {
    int spacing_between = icon_size.x / 4;
    // esquina inferior izquierda (tamaño pantalla - icono - padding)
    return SDL2pp::Point(spacing_between, screen_size.y - icon_size.y - spacing_between);
}

SDL2pp::Point RenderableHUDHealth::get_number_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size, int spacing) const {
    // calcular posicion del hud
    SDL2pp::Point icon_pos = get_icon_position(screen_size, icon_size);
    // posicion calculada anteriormente + tamaño del icono + espacio entre icono y numero
    return SDL2pp::Point(icon_pos.x + icon_size.x + spacing, icon_pos.y);
}
