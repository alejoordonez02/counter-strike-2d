#include "client/renderables/renderable_player.h"

#include <utility>

#include "client/providers/animation_provider.h"
#include "common/network/dtos/snapshot_dto.h"

RenderablePlayer::RenderablePlayer(
    uint16_t player_id, std::shared_ptr<AnimationProvider> animation_provider):
    player_id(player_id), is_terrorist(true), position(0, 0), facing_angle(0),
    is_shooting(false), was_hurt(false), is_walking(false), is_dead(false),
    current_weapon(WeaponName::NONE), legs(animation_provider),
    gun(animation_provider), animation_provider(animation_provider) {
    load_animation("holding_pistol");
    load_animation("holding_knife");
    load_animation("holding_rifle");
    load_animation("placing_bomb");
    load_animation("idle");
    animations["death_icon"] = animation_provider->make_animation("death");
    current_animation = animations["idle"].get();
}

void RenderablePlayer::load_animation(const std::string& animation_name) {
    std::string sufix_name = is_terrorist ? "terrorist_" : "counter_terrorist_";
    std::string skin_id = "1_";
    std::string full_name = sufix_name + skin_id + animation_name;

    animations[animation_name] = animation_provider->make_animation(full_name);
}

void RenderablePlayer::update(const PlayerDTO& player) {
    this->position.x = player.x;
    this->position.y = player.y;
    this->is_walking = player.is_walking;
    this->is_shooting = player.is_shooting;

    if (player.is_dead) {
        current_animation = animations["death_icon"].get();
        current_animation->start_fadeout();
        current_animation->update();
        return;
    }

    // ahora usa float y resta posiciones correctamente
    this->facing_angle =
        calculate_facing_angle(player.x, player.y, player.aim_x, player.aim_y);
    current_weapon = player.current_weapon;

    // siempre actualiza las piernas
    legs.update(this->position, this->facing_angle, is_walking);

    // segun el tipo de arma adopta sprite diferente
    if (this->current_weapon == WeaponName::NONE) {
        current_animation = animations["idle"].get();
    } else if (this->current_weapon == WeaponName::KNIFE) {
        current_animation = animations["holding_knife"].get();
    } else if (this->current_weapon == WeaponName::GLOCK) {
        current_animation = animations["holding_pistol"].get();
    } else if (this->current_weapon == WeaponName::BOMB) {
        current_animation = animations["placing_bomb"].get();
    } else {
        current_animation = animations["holding_rifle"].get();
    }
    // renderizar siempre el arma
    gun.update(this->position, Position(player.aim_x, player.aim_y),
               this->facing_angle, this->current_weapon, this->is_shooting);

    current_animation->update();
}

void RenderablePlayer::render(SDL2pp::Renderer& renderer) {
    // NOTE: el orden de renderizado indica como un sprite "pisa" a otro

    double angle = this->facing_angle;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (current_animation->is_fading_out &&
        !current_animation->update_fadeout()) {
        // si está en fadeout, no lo renderiza
        return;
    }
    legs.render(renderer);
    current_animation->render(renderer, position, flip, angle);
    gun.render(renderer);
}

/*
 * importantísimo acá usar float: las direcciones unitarias y por lo tanto nunca
 * ninguna de sus componentes va a ser mayor a uno
 * */
double RenderablePlayer::calculate_facing_angle(float pos_x, float pos_y,
                                                float aim_x, float aim_y) {
    // float dx = aim_x - pos_x;
    // float dy = aim_y - pos_y;
    /*
     * Ahora la dirección que me llega es por así decirlo la posta, así que no
     * tengo que hacer ninguna cuenta más que pasar de vector a ángulo con atan2
     * */
    (void)pos_x;
    (void)pos_y;
    double angle = std::atan2(aim_y, aim_x) * 180.0 / M_PI;
    return angle + 90.0;  // según alineacion del jugador
}

void RenderablePlayer::skip_frames(uint8_t frames_to_skip) {
    current_animation->skip_frames(frames_to_skip);
    if (this->is_walking) {
        legs.skip_frames(frames_to_skip);
    }
}

RenderablePlayer::~RenderablePlayer() {}
