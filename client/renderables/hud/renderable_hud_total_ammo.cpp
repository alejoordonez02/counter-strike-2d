#include "client/renderables/hud/renderable_hud_total_ammo.h"

RenderableHUDTotalAmmo::RenderableHUDTotalAmmo(std::shared_ptr<AnimationProvider> animation_provider):
numbers(animation_provider) {
    animations["glock"] = animation_provider->make_animation("glock");
    animations["ak47"] = animation_provider->make_animation("ak47");
    animations["m3"] = animation_provider->make_animation("m3");
    animations["awp"] = animation_provider->make_animation("awp");
    animations["knife"] = animation_provider->make_animation("knife");
    animations["bomb"] = animation_provider->make_animation("bomb");
    animations["none"] = animation_provider->make_animation("none");

    current_animation = animations["glock"].get();
}

void RenderableHUDTotalAmmo::update_gun_icon(WeaponName weapon_name) {
    if (weapon_name == WeaponName::GLOCK) {
        current_animation = animations["glock"].get();
    } else if (weapon_name == WeaponName::AK47) {
        current_animation = animations["ak47"].get();
    } else if (weapon_name == WeaponName::M3) {
        current_animation = animations["m3"].get();
    } else if (weapon_name == WeaponName::AWP) {
        current_animation = animations["awp"].get();
    } else if (weapon_name == WeaponName::KNIFE) {
        current_animation = animations["knife"].get();
    } else if (weapon_name == WeaponName::BOMB) {
        current_animation = animations["bomb"].get();
    } else {
        current_animation = animations["none"].get();
    }
}

void RenderableHUDTotalAmmo::update(const PrivateWeaponDTO& weapon_data) {
    numbers.update(weapon_data.total_ammo);

    update_gun_icon(WeaponName::BOMB);
}


Position RenderableHUDTotalAmmo::get_icon_position(const Position& screen_size, const Position& icon_size) {
    int spacing_between = icon_size.x / 4;
    int MAX_DIGITS = 4;
    // esquina inferior derecha dejando un margen para loaded ammo
    int x = screen_size.x - (icon_size.x + spacing_between) * MAX_DIGITS;
    int y = screen_size.y - icon_size.y;
    return Position(x, y);
}

void RenderableHUDTotalAmmo::render(SDL2pp::Renderer& renderer) {
    bool is_camera_enabled = false;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Position icon_size = current_animation->get_animation_size();
    // espacio entre el icono y el numero
    int spacing_between = icon_size.x / 4;

    // calculate positions
    Position screen_size = Position(renderer.GetOutputSize().x, renderer.GetOutputSize().y);
    
    Position icon_pos = get_icon_position(screen_size, icon_size);
    Position number_pos = Position(icon_pos.x + icon_size.x + spacing_between, icon_pos.y);

    // render icon and numbers
    current_animation->render(renderer, icon_pos, flip, 0, is_camera_enabled);
    numbers.render(renderer, number_pos, is_camera_enabled);
}


