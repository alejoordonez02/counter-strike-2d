#include "renderable_player.h"
#include "../../common/snapshot.h"
#include "../texture_provider.h"


RenderablePlayer::RenderablePlayer(uint16_t player_id): 
    player_id(player_id),    
    position(0, 0),
    facing_angle(0), 
    is_shooting(false), 
    was_hurt(false), 
    is_walking(false), 
    is_dead(false), 
    is_terrorist(true),
    current_weapon(WeaponType::None)
{
    load_animation("walking");
    load_animation("shooting");
    load_animation("idle");
    current_animation = animations["idle"];
}


void RenderablePlayer::load_animation(const std::string& animation_name) {
    std::string sufix_name = "counter_terrorist_";
    if(is_terrorist){
        sufix_name = "terrorist_";
    }
    animations[animation_name] = new Animation(
        *TexturesProvider::get_texture(sufix_name + "1"),      // obtiene toda la imagen
        AnimationProvider::get_animation_data(sufix_name + animation_name)    // se encarga de dividir al imagen en frames
    );
}


void RenderablePlayer::update(PlayerDTO& player)
{
    this->facing_angle = player.facing_angle;
    
    position.x = player.x;
    position.y = player.y;

    // resto de las animaciones
    if(player.is_walking){
        // le pide a renderable_legs que se muevan y se animen
        // current_animation = animations["terrorist_walking"];
    } else {
        current_animation = animations["terrorist_idle"];
    }
    // } else if (player.is_shooting){
    //     current_animation = animations["terrorist_shooting"];
    // }
    
    current_animation->update();
}




void RenderablePlayer::render(SDL2pp::Renderer &renderer){
    double angle = this->facing_angle;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    current_animation->render(renderer, position, flip, angle);
}



RenderablePlayer::~RenderablePlayer()
{

}