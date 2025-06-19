#include "client/renderables/renderable_legs.h"

#include <memory>
#include <string>
#include <utility>

#include "client/animation_provider.h"

RenderableLegs::RenderableLegs(
        std::shared_ptr<AnimationProvider> animation_provider):
        position(0, 0),
        facing_angle(0),
        current_animation(nullptr),
        animation_provider(animation_provider) {
    load_animation("legs");
    current_animation = animations["legs"].get();
}

void RenderableLegs::load_animation(const std::string& animation_name) {
    animations[animation_name] = animation_provider->make_animation(animation_name);
}

void RenderableLegs::update(const SDL2pp::Point& position, double facing_angle, bool is_walking) {
    // Si no esta caminando ir al frame 0
    if(!is_walking){
        current_animation->reset();
        return;
    }
    
    this->facing_angle = facing_angle;

    // NOTE: Para que las piernas queden alineadas
    // respecto al jugador
    double radians = facing_angle * M_PI / 180.0;
    double offset = -3;
    this->position.x = position.x + std::cos(radians) * offset;
    this->position.y = position.y + std::sin(radians) * offset;

    current_animation->update();
}

void RenderableLegs::render(SDL2pp::Renderer& renderer) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    current_animation->render(renderer, position, flip, this->facing_angle);
}

void RenderableLegs::skip_frames(uint8_t frames_to_skip){
    current_animation->skip_frames(frames_to_skip);
}

RenderableLegs::~RenderableLegs() {}
