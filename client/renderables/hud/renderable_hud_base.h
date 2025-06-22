#ifndef CLIENT_RENDERABLES_RENDERABLE_HUD_BASE_H
#define CLIENT_RENDERABLES_RENDERABLE_HUD_BASE_H

#include <memory>
#include <string>
#include "SDL2pp/Point.hh"
#include "common/position.h"
#include "SDL2pp/Renderer.hh"
#include "client/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/hud/renderable_numbers.h"

class RenderableHUDBase {
protected:
    std::shared_ptr<AnimationProvider> animation_provider;
    std::unique_ptr<Animation> icon_animation;
    RenderableNumbers numbers;

public:
    RenderableHUDBase(std::shared_ptr<AnimationProvider> animation_provider)
        : animation_provider(animation_provider), numbers(animation_provider) {
        numbers.load_numbers();
    }

    virtual ~RenderableHUDBase() {}

    virtual std::string get_icon_name() const = 0;
    virtual Position get_icon_position(const Position& screen_size, const Position& icon_size) const = 0;
    virtual Position get_number_position(const Position& screen_size, const Position& icon_size, int spacing) const = 0;

    virtual void update(uint number) {
        numbers.update(number);
    }

    virtual void update(const std::string& str) {
        numbers.update_string(str);
    }

    virtual void render(SDL2pp::Renderer& renderer) {
        /** 
         * Siempre se calcula el tamaño de la pantalla, ya que permitiria
         * hacer un resize de la misma en tiempo real
         */
        bool is_camera_enabled = false;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        Position icon_size = icon_animation->get_animation_size();
        // espacio entre el icono y el numero
        int spacing_between = icon_size.x / 4;

        // calculate positions
        Position screen_size = Position(renderer.GetOutputSize().x, renderer.GetOutputSize().y);
        
        Position icon_pos = get_icon_position(screen_size, icon_size);
        Position number_pos = get_number_position(screen_size, icon_size, spacing_between);

        // render icon and numbers
        icon_animation->render(renderer, icon_pos, flip, 0, is_camera_enabled);
        numbers.render(renderer, number_pos, is_camera_enabled);
    }
};

#endif
