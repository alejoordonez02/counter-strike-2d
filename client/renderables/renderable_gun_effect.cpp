#include "client/renderables/renderable_gun_effect.h"

#include <memory>
#include <random>
#include <string>
#include <utility>


RenderableGunEffect::RenderableGunEffect(
        std::shared_ptr<AnimationProvider> animation_provider):
        position(0, 0),
        gun_position(0, 0),
        facing_angle(0),
        current_animation(nullptr),
        animation_provider(animation_provider) {
    load_animation("flare3");
    load_animation("knifeslash");
    load_animation("none");
    // load_animation("fragments");

    // por default no tiene armas
    current_animation = animations["none"].get();
}

void RenderableGunEffect::load_animation(const std::string& animation_name) {
    animations[animation_name] =
        animation_provider->make_animation(animation_name);
}

void RenderableGunEffect::update(const Position& player_position,
                                 const Position& gun_position,
                                 const Position& aim_position,
                                 double facing_angle, WeaponName weapon_type,
                                 bool is_shooting) {
    this->gun_position = gun_position;
    this->aim_position = aim_position;

    if (!is_shooting || weapon_type == WeaponName::NONE) {
        current_animation = animations["none"].get();
    } else if (is_shooting && weapon_type == WeaponName::KNIFE) {
        // current_animation = animations["knifeslash"].get();
    } else if (is_shooting && (weapon_type == WeaponName::M3 || weapon_type == WeaponName::GLOCK || weapon_type == WeaponName::AK47 || weapon_type == WeaponName::AWP)) {
        current_animation = animations["flare3"].get();
    } else if (!is_shooting) {
        current_animation = animations["none"].get();
    }

    // NOTE: Para que el arma quede alineada con el eje X
    Position texture_size = current_animation->get_animation_size();
    this->facing_angle = facing_angle + 90;
    double radians = (this->facing_angle) * M_PI / 180.0;
    double offset = -texture_size.x / 2;
    this->position.x =
        player_position.x - texture_size.x / 4 + std::cos(radians) * offset;
    this->position.y =
        player_position.y - texture_size.y / 4 + std::sin(radians) * offset;

    current_animation->update();
}

void RenderableGunEffect::render_line(SDL2pp::Renderer& renderer) {
    // Un solo valor random base
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> base_dist(0.0f, 1.0f);
    float base = base_dist(gen);

    // Derivar los valores a partir de base
    float length = 10.0f + base * 50.0f;             // 10 a 60
    int thickness = 1 + static_cast<int>(base * 3);  // 1 a 4
    int alpha = 64 + static_cast<int>(base * 191);   // 64 a 255

    // calcular posicion de inicio y fin de la línea
    SDL2pp::Point start(position.x + 25, position.y + 25);
    SDL2pp::Point end_point;
    end_point.x = start.x + aim_position.x * length;
    end_point.y = start.y + aim_position.y * length;

    // ajustar segun la camara
    Camera::modify_center_point(start);
    Camera::modify_center_point(end_point);

    SDL_SetRenderDrawBlendMode(renderer.Get(), SDL_BLENDMODE_BLEND);
    renderer.SetDrawColor(255, 255, 0, alpha);

    // simular grosor de la línea con varias lineas
    if (thickness <= 1) {
        SDL_RenderDrawLine(renderer.Get(), start.x, start.y, end_point.x,
                           end_point.y);
    } else {
        for (int i = -thickness / 2; i <= thickness / 2; ++i) {
            SDL_RenderDrawLine(renderer.Get(), start.x + i, start.y + i,
                               end_point.x + i, end_point.y + i);
        }
    }
    renderer.SetDrawColor(0, 0, 0, 0);
}

void RenderableGunEffect::render(SDL2pp::Renderer& renderer) {
    // Si el efecto actual es flare3, dibujar la línea amarilla
    if (current_animation == animations["flare3"].get()) {
        render_line(renderer);
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    current_animation->render(renderer, position, flip, this->facing_angle);
}

void RenderableGunEffect::skip_frames(uint8_t frames_to_skip) {
    current_animation->skip_frames(frames_to_skip);
}

RenderableGunEffect::~RenderableGunEffect() {}
