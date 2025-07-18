#include "client/renderables/renderable_gun.h"

#include <memory>
#include <string>
#include <utility>

#include "client/providers/animation_provider.h"

RenderableGun::RenderableGun(
    std::shared_ptr<AnimationProvider> animation_provider):
    position(0, 0), facing_angle(0), current_animation(nullptr),
    animation_provider(animation_provider), gun_effect(animation_provider) {
    load_animation("held_bomb");
    load_animation("held_knife");
    load_animation("held_glock");
    load_animation("held_ak47");
    load_animation("held_m3");
    load_animation("held_awp");
    // por default no tiene armas
    current_animation = nullptr;
}

void RenderableGun::load_animation(const std::string& animation_name) {
    animations[animation_name] =
        animation_provider->make_animation(animation_name);
}

void RenderableGun::update(const Position& player_position,
                           const Position& aim_position, double facing_angle,
                           WeaponName weapon_type, bool is_shooting) {
    if (weapon_type == WeaponName::NONE) {
        current_animation = nullptr;
        return;
    } else if (weapon_type == WeaponName::BOMB) {
        current_animation = animations["held_bomb"].get();
    } else if (weapon_type == WeaponName::KNIFE) {
        current_animation = animations["held_knife"].get();
    } else if (weapon_type == WeaponName::GLOCK) {
        current_animation = animations["held_glock"].get();
    } else if (weapon_type == WeaponName::AK47) {
        current_animation = animations["held_ak47"].get();
    } else if (weapon_type == WeaponName::M3) {
        current_animation = animations["held_m3"].get();
    } else if (weapon_type == WeaponName::AWP) {
        current_animation = animations["held_awp"].get();
    }

    // NOTE: Para que el arma quede alineada con el eje X
    // ya que SDL tiene una forma distinta de calcular los angulos
    // 0 = 0°, pi/2 = 90°, pi = 180°/-180°, -pi/2 = -90°, ...
    this->facing_angle = facing_angle;
    double radians = (this->facing_angle + 90) * M_PI / 180.0;
    double offset = -20;  // TODO: Hardcodeado segun tamaño textura
    this->position.x = player_position.x + std::cos(radians) * offset;
    this->position.y = player_position.y + std::sin(radians) * offset;

    // actualiza la animacion del efecto del disparo
    gun_effect.update(player_position, position, aim_position,
                      this->facing_angle, weapon_type, is_shooting);

    if (current_animation == nullptr) {
        return;
    }
    current_animation->update();
}

void RenderableGun::render(SDL2pp::Renderer& renderer) {
    // No hay arma para renderizar
    if (current_animation == nullptr) {
        return;
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    current_animation->render(renderer, position, flip, this->facing_angle);
    gun_effect.render(renderer);
}

void RenderableGun::skip_frames(uint8_t frames_to_skip) {
    // No hay arma para renderizar
    if (current_animation == nullptr) {
        return;
    }
    current_animation->skip_frames(frames_to_skip);
}

RenderableGun::~RenderableGun() {}
