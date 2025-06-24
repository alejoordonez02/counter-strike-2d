#include "client/renderables/hud/renderable_hud_loaded_ammo.h"

#include <utility>
#include "client/providers/animation_provider.h"
#include "renderable_numbers.h"

RenderableHUDLoadedAmmo::RenderableHUDLoadedAmmo(std::shared_ptr<AnimationProvider> animation_provider)
    : RenderableHUDBase(animation_provider) {
    icon_animation = animation_provider->make_animation(get_icon_name());
}

std::string RenderableHUDLoadedAmmo::get_icon_name() const {
    return "|";
}

Position RenderableHUDLoadedAmmo::get_icon_position(const Position& screen_size, const Position& icon_size) const {
    int spacing_between = icon_size.x / 4;
    int MAX_DIGITS = 6;
    // esquina inferior derecha
    int x = screen_size.x - icon_size.x * MAX_DIGITS - spacing_between;
    int y = screen_size.y - (icon_size.y + spacing_between) * 2;    // para dejar espacio al ammo
    return Position(x, y);
}

Position RenderableHUDLoadedAmmo::get_number_position(const Position& screen_size, const Position& icon_size, int spacing) const {
    Position icon_pos = get_icon_position(screen_size, icon_size);
    // Los números van a la derecha del icono
    return Position(icon_pos.x + icon_size.x + spacing, icon_pos.y);
}
