#include "client/renderables/renderable_gun_effect.h"
#include "client/animation_provider.h"
#include "client/gameloop.h"

#include <memory>
#include <string>
#include <utility>

#define EFFECT_COUNTER_TIME 0.05f
// ej. 30 fps * 0.2f = 6 => cada 6 ticks hace el flare

RenderableGunEffect::RenderableGunEffect(
        std::shared_ptr<AnimationProvider> animation_provider):
        position(0, 0),
        facing_angle(0),
        current_animation(nullptr),
        animation_provider(animation_provider),
        effect_timer(0) {
    load_animation("flare3");
    load_animation("knifeslash");
    // load_animation("fragments");
    
    // por default no tiene armas
    current_animation = animations["flare3"].get();
}

void RenderableGunEffect::load_animation(const std::string& animation_name) {
    animations[animation_name] = animation_provider->make_animation(animation_name);
}

void RenderableGunEffect::update(const SDL2pp::Point& player_position, double facing_angle, 
                           WeaponType weapon_type, bool is_shooting) {

    if(!is_shooting || weapon_type == WeaponType::None) {
        current_animation = nullptr;
        effect_timer = 0;
        return;
    } else if (weapon_type == WeaponType::Bomb) {
        // current_animation = animations["bomb_explosion"].get();
    } else if (weapon_type == WeaponType::Knife) {
        current_animation = animations["knifeslash"].get();
    } else if (is_shooting && effect_timer < EFFECT_COUNTER_TIME * FRAME_RATE){
        current_animation = animations["flare3"].get();
        effect_timer++;
    } else if (is_shooting && effect_timer >= EFFECT_COUNTER_TIME * FRAME_RATE) {
        current_animation = nullptr;
        effect_timer = 0;
    }

    if(current_animation == nullptr) {
        return;
    }
    // NOTE: Para que el arma quede alineada con el eje X
    SDL2pp::Point texture_size = current_animation->get_animation_size();
    this->facing_angle = facing_angle + 90;
    double radians = (this->facing_angle) * M_PI / 180.0;
    double offset = -50;        // TODO: Hardcodeado segun tamaño textura
    this->position.x = player_position.x - texture_size.GetX()/4 + std::cos(radians) * offset;
    this->position.y = player_position.y - texture_size.GetY()/4 + std::sin(radians) * offset;

    std::cout << "this->facing_angle. effect" << this->facing_angle << std::endl;

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
