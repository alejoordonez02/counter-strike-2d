#include "client/renderables/renderable_pointer.h"

RenderablePointer::RenderablePointer(std::shared_ptr<AnimationProvider> animation_provider){
    animations["red_pointer"] = animation_provider->make_animation("red_pointer");
    animations["green_pointer"] = animation_provider->make_animation("green_pointer");
}

void RenderablePointer::update(bool is_attacking) {
    if(is_attacking){
        current_animation = animations["red_pointer"].get();
    } else {
        current_animation = animations["green_pointer"].get();
    }

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    Position size = current_animation->get_animation_size();
    x = mx - size.x/2;
    y = my - size.y/2;
    current_animation->update();
}

void RenderablePointer::render(SDL2pp::Renderer& renderer) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    // desactiva la camara
    current_animation->render(renderer, Position(x, y), flip, 0.0, false);
}
