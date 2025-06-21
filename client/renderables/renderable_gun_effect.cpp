#include "client/renderables/renderable_gun_effect.h"
#include "client/animation_provider.h"
#include "client/gameloop.h"
#include "client/camera.h"

#include "common/position.h"

#include <memory>
#include <string>
#include <utility>

#define EFFECT_COUNTER_TIME 0.1f
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

void RenderableGunEffect::update(const Position& player_position, const Position& gun_position, const Position& aim_position, double facing_angle, 
                           WeaponType weapon_type, bool is_shooting) {
    this->gun_position = gun_position;
    this->aim_position = aim_position;

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
    Position texture_size = current_animation->get_animation_size();
    this->facing_angle = facing_angle + 90;
    double radians = (this->facing_angle) * M_PI / 180.0;
    double offset = -texture_size.x / 2;
    this->position.x = player_position.x - texture_size.x / 4 + std::cos(radians) * offset;
    this->position.y = player_position.y - texture_size.y / 4 + std::sin(radians) * offset;

    current_animation->update();
}

void RenderableGunEffect::render_line(SDL2pp::Renderer& renderer) {
    // calcular punto de inicio de la línea
    // NOTE: Valor hardcodeado en base al tamaño de la textura
    SDL2pp::Point start = SDL2pp::Point(position.x + 25, position.y + 25);
    
    // calcular punto final de la línea
    float length = 200.0f; // largo de la línea
    SDL2pp::Point end_point;
    end_point.x = start.x + aim_position.x * length;
    end_point.y = start.y + aim_position.y * length;

    // modificar los puntos para que estén centrados en la camara
    Camera::modify_center_point(start);
    Camera::modify_center_point(end_point);
    renderer.SetDrawColor(255, 255, 0, 128); // Amarillo
    SDL_RenderDrawLine(renderer.Get(), start.x, start.y, end_point.x, end_point.y);
    renderer.SetDrawColor(0, 0, 0, 0); // Restaurar color de fondo
}


void RenderableGunEffect::render(SDL2pp::Renderer& renderer) {
    // No hay arma para renderizar
    if(current_animation == nullptr) {
        return;
    }
    
    // Si el efecto actual es flare3, dibujar la línea amarilla
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
