#include "client/renderables/renderable_gun_effect.h"
#include "client/animation_provider.h"

#include <memory>
#include <string>
#include <utility>


RenderableGunEffect::RenderableGunEffect(
        std::shared_ptr<AnimationProvider> animation_provider):
        position(0, 0),
        facing_angle(0),
        current_animation(nullptr),
        animation_provider(animation_provider) {
    load_animation("flare3");
    load_animation("knifeslash");
    // load_animation("fragments");
    
    // por default no tiene armas
    current_animation = animations["flare3"].get();
}

void RenderableGunEffect::load_animation(const std::string& animation_name) {
    animations[animation_name] = animation_provider->make_animation(animation_name);
}

void RenderableGunEffect::update(const SDL2pp::Point& position, double facing_angle, 
                           WeaponType weapon_type, bool is_shooting) {
    static int flare_timer = 0;
    std::cout << "flare_timer = " << flare_timer << "is_shooting=" << is_shooting << std::endl;
    is_shooting = true;
    if(!is_shooting || weapon_type == WeaponType::None) {
        current_animation = nullptr;
        flare_timer = 0;
        return;
    } else if (weapon_type == WeaponType::Bomb) {
        // current_animation = animations["bomb_explosion"].get();
    } else if (weapon_type == WeaponType::Knife) {
        current_animation = animations["knifeslash"].get();
    } else if (is_shooting && flare_timer < 5){
        std::cout << "menos de 5" << flare_timer << std::endl;
        current_animation = animations["flare3"].get();
        flare_timer++;
    } else if (is_shooting && flare_timer >= 5) {
        std::cout << "mas de 5" << flare_timer << std::endl;
        current_animation = nullptr;
        flare_timer = 0;
    }


    // NOTE: Para que el arma quede alineada con el eje X
    // ya que en SDL, 0 grados es es hacia la derecha
    this->facing_angle = facing_angle;
    double radians = (this->facing_angle + 90) * M_PI / 180.0;
    double offset = -20;        // TODO: Hardcodeado segun tamaño textura
    this->position.x = position.x + std::cos(radians) * offset;
    this->position.y = position.y + std::sin(radians) * offset;


    if(current_animation == nullptr) {
        return;
    }
    current_animation->update();
}

void RenderableGunEffect::render(SDL2pp::Renderer& renderer) {
    // No hay arma para renderizar
    if(current_animation == nullptr) {
        return;
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    current_animation->render(renderer, position, flip, this->facing_angle);
}

void RenderableGunEffect::skip_frames(uint8_t frames_to_skip){
     // No hay arma para renderizar
    if(current_animation == nullptr) {
        return;
    }
    current_animation->skip_frames(frames_to_skip);
}

RenderableGunEffect::~RenderableGunEffect() {}
