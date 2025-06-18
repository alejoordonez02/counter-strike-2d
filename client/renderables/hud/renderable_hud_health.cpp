#include "client/renderables/hud/renderable_hud_health.h"
#include "client/animation_provider.h"

#include <utility>
#include "renderable_numbers.h"

RenderableHUDHealth::RenderableHUDHealth(
        std::shared_ptr<AnimationProvider> animation_provider):
        animation_provider(animation_provider),
        heart_icon_animation(nullptr),
        heart_numbers(animation_provider){
    // inicializar datos
    heart_icon_animation = std::move(animation_provider->make_animation("heart"));
    heart_numbers.load_numbers();
}


void RenderableHUDHealth::update(uint8_t number) {
    heart_numbers.update(number);

    // NOTE: mas adelante se podria hacer para que el color de la salud cambie
    // dependiendo de la cantidad de vida que tenga el jugador
}

void RenderableHUDHealth::render(SDL2pp::Renderer& renderer) {
    /** 
     * Siempre se calcula el tamaño de la pantalla, ya que permitiria
     * hacer un resize de la misma en tiempo real
     */
    bool is_camera_enabled = false;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL2pp::Point heart_icon_size = heart_icon_animation->get_animation_size();
    // espacio entre el icono del corazon y el numero
    int spacing_between = heart_icon_size.x / 4; 
    
    // calculate positions
    SDL2pp::Point heart_icon_position = SDL2pp::Point(spacing_between, renderer.GetOutputSize().y - (heart_icon_size.y) - spacing_between);
    SDL2pp::Point number_position = SDL2pp::Point(heart_icon_position.x + (heart_icon_size.x) + spacing_between, renderer.GetOutputSize().y - (heart_icon_size.y) - spacing_between);

    // render heart icon and numbers
    heart_icon_animation->render(renderer, heart_icon_position, flip, 0, is_camera_enabled);
    heart_numbers.render(renderer, number_position, is_camera_enabled);
}

RenderableHUDHealth::~RenderableHUDHealth() {}
