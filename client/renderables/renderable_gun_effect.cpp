#include "client/renderables/renderable_gun_effect.h"
#include "client/animation_provider.h"
#include "client/gameloop.h"
#include "client/camera.h"

#include <memory>
#include <string>
#include <utility>
#include "renderable_gun_effect.h"

#define EFFECT_COUNTER_TIME 0.05f
// ej. 30 fps * 0.2f = 6 => cada 6 ticks hace el flare

RenderableGunEffect::RenderableGunEffect(
        std::shared_ptr<AnimationProvider> animation_provider):
        position(0, 0),
        gun_position(0, 0),
        facing_angle(0),
        current_animation(nullptr),
        animation_provider(animation_provider),
        effect_timer(0) {
    load_animation("flare3");
    load_animation("knifeslash");
    // load_animation("fragments");
    
    // por default no tiene armas
    current_animation = nullptr;
}

void RenderableGunEffect::load_animation(const std::string& animation_name) {
    animations[animation_name] = animation_provider->make_animation(animation_name);
}

void RenderableGunEffect::update(const SDL2pp::Point& player_position, const SDL2pp::Point& gun_position, double facing_angle, 
                           WeaponType weapon_type, bool is_shooting) {
    this->gun_position = gun_position;
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
    double offset = -texture_size.GetX()/2;
    this->position.x = player_position.x - texture_size.GetX()/4 + std::cos(radians) * offset;
    this->position.y = player_position.y - texture_size.GetY()/4 + std::sin(radians) * offset;

    current_animation->update();
}

void RenderableGunEffect::render_line(SDL2pp::Renderer& renderer) {
    // NOTE: Se podria cambiar para que tome a partir del aim, pero al no ser absoluto
    // es mejor que tome la posicion del mouse
    int mouse_x = 0, mouse_y = 0;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL2pp::Point modified_position = gun_position;
    modified_position.x += 10;
    modified_position.y += 10;
    Camera::modify_center_point(modified_position);
    renderer.SetDrawColor(255, 255, 0, 10); // Amarillo
    SDL_RenderDrawLine(renderer.Get(), modified_position.x, modified_position.y, mouse_x, mouse_y);
    renderer.SetDrawColor(0, 0, 0, 0); // Restaurar color de fondo
}


void RenderableGunEffect::render(SDL2pp::Renderer& renderer) {
    // No hay arma para renderizar
    if(current_animation == nullptr) {
        return;
    }
    // Si el efecto actual es flare3, dibujar la línea amarilla hasta el mouse
    if (current_animation == animations["flare3"].get()) {
        render_line(renderer);
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
