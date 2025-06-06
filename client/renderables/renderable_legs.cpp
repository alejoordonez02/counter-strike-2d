#include "renderable_legs.h"
#include "../../common/snapshot.h"
#include "../texture_provider.h"
#include "../animation_provider.h"


RenderableLegs::RenderableLegs(std::shared_ptr<AnimationProvider> animation_provider):
    position(0, 0),
    facing_angle(0),
    current_animation(nullptr),
    animation_provider(animation_provider)
{
    load_animation("legs");
    current_animation = animations["legs"].get();
}


void RenderableLegs::load_animation(const std::string& animation_name) {
    animations[animation_name] = std::move(animation_provider->make_animation(animation_name));
}


void RenderableLegs::update(const SDL2pp::Point& position, double facing_angle)
{
    this->position = position;
    this->facing_angle = facing_angle;

    current_animation->update();
}


void RenderableLegs::render(SDL2pp::Renderer &renderer){
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    current_animation->render(renderer, position, flip, this->facing_angle);
}



RenderableLegs::~RenderableLegs()
{

}