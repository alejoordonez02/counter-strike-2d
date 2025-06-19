#include "client/renderables/hud/renderable_hud_money.h"

#include <utility>
#include "client/animation_provider.h"
#include "renderable_numbers.h"

RenderableHUDMoney::RenderableHUDMoney(std::shared_ptr<AnimationProvider> animation_provider)
    : RenderableHUDBase(animation_provider) {
    icon_animation = animation_provider->make_animation(get_icon_name());
}

std::string RenderableHUDMoney::get_icon_name() const {
    return "money";
}

SDL2pp::Point RenderableHUDMoney::get_icon_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size) const {
    int spacing_between = icon_size.x / 4;
    int MAX_NUMBERS = 6;
    // esquina inferior derecha
    int x = screen_size.x - icon_size.x * MAX_NUMBERS - spacing_between;
    int y = screen_size.y - icon_size.y - spacing_between;
    return SDL2pp::Point(x, y);
}

SDL2pp::Point RenderableHUDMoney::get_number_position(const SDL2pp::Point& screen_size, const SDL2pp::Point& icon_size, int spacing) const {
    SDL2pp::Point icon_pos = get_icon_position(screen_size, icon_size);
    // Los números van a la derecha del icono
    return SDL2pp::Point(icon_pos.x + icon_size.x + spacing, icon_pos.y);
}
