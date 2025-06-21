#include "client/renderables/hud/renderable_hud_health.h"

RenderableHUDHealth::RenderableHUDHealth(std::shared_ptr<AnimationProvider> animation_provider)
    : RenderableHUDBase(animation_provider) {
    icon_animation = animation_provider->make_animation(get_icon_name());
}

std::string RenderableHUDHealth::get_icon_name() const {
    return "heart";
}

Position RenderableHUDHealth::get_icon_position(const Position& screen_size, const Position& icon_size) const {
    int spacing_between = icon_size.x / 4;
    // esquina inferior izquierda (tamaño pantalla - icono - padding)
    return Position(spacing_between, screen_size.y - icon_size.y - spacing_between);
}

Position RenderableHUDHealth::get_number_position(const Position& screen_size, const Position& icon_size, int spacing) const {
    // calcular posicion del hud
    Position icon_pos = get_icon_position(screen_size, icon_size);
    // posicion calculada anteriormente + tamaño del icono + espacio entre icono y numero
    return Position(icon_pos.x + icon_size.x + spacing, icon_pos.y);
}
