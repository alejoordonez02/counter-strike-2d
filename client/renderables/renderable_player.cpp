#include "client/renderables/renderable_player.h"

#include <utility>

#include "client/animation_provider.h"
#include "common/snapshot.h"

RenderablePlayer::RenderablePlayer(
    uint16_t player_id, std::shared_ptr<AnimationProvider> animation_provider):
    player_id(player_id), is_terrorist(true), position(0, 0), facing_angle(0),
    is_shooting(false), was_hurt(false), is_walking(false), is_dead(false),
    current_weapon(WeaponType::None), legs(animation_provider),
    animation_provider(animation_provider) {
    // load_animation("walking");
    load_animation("shooting");
    load_animation("idle");
    current_animation = animations["idle"].get();
}

void RenderablePlayer::load_animation(const std::string& animation_name) {
    std::string sufix_name = is_terrorist ? "terrorist_" : "counter_terrorist_";
    std::string skin_id = "1_";
    std::string full_name = sufix_name + skin_id + animation_name;
    
    animations[animation_name] = animation_provider->make_animation(full_name);
}

void RenderablePlayer::update(const PlayerData& player) {
    position.x = player.x;
    position.y = player.y;
    is_walking = player.is_walking;
    // ahora usa float y resta posiciones correctamente
    facing_angle =
        calculate_facing_angle(player.x, player.y, player.aim_x, player.aim_y);

    if (this->is_walking) {
        // le pide a renderable_legs que se muevan y se animen. No hace nada con
        // la textura original
        legs.update(position, this->facing_angle);
        current_animation = animations["shooting"].get();
    } else {
        current_animation = animations["idle"].get();
    }

    // adicionalmente se fija que tipo de arma tenes y en base a eso escoje la
    // textura if (player.weapon_type != knife){
    //     current_animation = animations["terrorist_standing_shoot"];
    // } else if (player.weapon_type == knife){
    //     current_animation = animations["terrorist_standing_knife"];
    // }
    // } else if (player.is_shooting){
    // para disparar necesita un arma y cambiar su textura
    // RenderableGun a su vez tiene un shooting, que le dice si poner el fuego
    // en el arma o no update_gun(x, y, gun_type, is_shooting) current_animation
    // = animations["terrorist_shooting"]; } else if (player.is_placing_bomb){
    // solo necesita cambiar su textura
    // current_animation = animations["terrorist_extending_arms"];
    // }

    current_animation->update();
}

void RenderablePlayer::render(SDL2pp::Renderer& renderer) {
    double angle = this->facing_angle;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    legs.render(renderer);
    current_animation->render(renderer, position, flip, angle);
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
    return angle + 90.0;  // según tu alineación
}

void RenderablePlayer::skip_frames(uint8_t frames_to_skip) {
    current_animation->skip_frames(frames_to_skip);
    if (this->is_walking) {
        legs.skip_frames(frames_to_skip);
    }
}

RenderablePlayer::~RenderablePlayer() {}
