#include "renderable_player.h"
#include "../../common/snapshot.h"
#include "../texture_provider.h"


RenderablePlayer::RenderablePlayer(uint8_t player_id): 
    player_id(player_id),    
    x(0), 
    y(0), 
    facing_angle(0.0f), 
    is_shooting(false), 
    was_hurt(false), 
    is_walking(false), 
    is_dead(false), 
    current_weapon(WeaponType::None),
    animation(*TextureProvider::get_texture("terrorist_1"))
{
    // obtener de texture provider el nombre de "terrorista". 
    // ella misma se encarga de fijarse las animaciones y demás
}



void RenderablePlayer::update(PlayerDTO& player)
{
    this->facing_angle = player.facing_angle;
    
    this->x = player.x;
    this->y = player.y;
}




void RenderablePlayer::render(SDL2pp::Renderer &renderer){
    double angle = this->facing_angle;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    animation.render(renderer, SDL2pp::Rect(this->x, this->y, 32, 32), flip, angle);
}



RenderablePlayer::~RenderablePlayer()
{

}