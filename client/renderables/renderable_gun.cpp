#include "client/renderables/renderable_gun.h"
#include "client/animation_provider.h"

#include <memory>
#include <string>
#include <utility>


RenderableGun::RenderableGun(
        std::shared_ptr<AnimationProvider> animation_provider):
        position(0, 0),
        facing_angle(0),
        current_animation(nullptr),
        animation_provider(animation_provider),
        gun_effect(animation_provider) {
    load_animation("bomb");
    load_animation("knife");
    load_animation("glock");
    load_animation("ak47");
    load_animation("m3");
    load_animation("awp");
    // por default no tiene armas
    current_animation = nullptr;
}

void RenderableGun::load_animation(const std::string& animation_name) {
    animations[animation_name] = animation_provider->make_animation(animation_name);
}

void RenderableGun::update(const SDL2pp::Point& player_position, double facing_angle, 
                           WeaponType weapon_type, bool is_shooting) {
    if(weapon_type == WeaponType::None) {
        current_animation = nullptr;
        return;
    } else if (weapon_type == WeaponType::Bomb) {
        current_animation = animations["bomb"].get();
    } else if (weapon_type == WeaponType::Knife) {
        current_animation = animations["knife"].get();
    } else if (weapon_type == WeaponType::Glock) {
        current_animation = animations["glock"].get();
    } else if (weapon_type == WeaponType::AK47) {
        current_animation = animations["ak47"].get();
    } else if (weapon_type == WeaponType::M3) {
        current_animation = animations["m3"].get();
    } else if (weapon_type == WeaponType::AWP) {
        current_animation = animations["awp"].get();
    }


    // NOTE: Para que el arma quede alineada con el eje X
    // ya que SDL tiene una forma distinta de calcular los angulos
    // 0 = 0°, pi/2 = 90°, pi = 180°/-180°, -pi/2 = -90°, ...
    this->facing_angle = facing_angle;
    double radians = (this->facing_angle + 90) * M_PI / 180.0;
    double offset = -20;        // TODO: Hardcodeado segun tamaño textura
    this->position.x = player_position.x + std::cos(radians) * offset;
    this->position.y = player_position.y + std::sin(radians) * offset;
    
    std::cout << "this->facing_angle. gun" << this->facing_angle << std::endl;
    
    // actualiza la animacion del efecto del disparo
    gun_effect.update(player_position, this->facing_angle, weapon_type, is_shooting);

    if(current_animation == nullptr) {
        return;
    }
    current_animation->update();
}

void RenderableGun::render(SDL2pp::Renderer& renderer) {
    // No hay arma para renderizar
    if(current_animation == nullptr) {
        return;
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    current_animation->render(renderer, position, flip, this->facing_angle);
    gun_effect.render(renderer);
}

void RenderableGun::skip_frames(uint8_t frames_to_skip){
     // No hay arma para renderizar
    if(current_animation == nullptr) {
        return;
    }
    current_animation->skip_frames(frames_to_skip);
}

RenderableGun::~RenderableGun() {}
