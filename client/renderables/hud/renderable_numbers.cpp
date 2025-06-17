#include "client/renderables/hud/renderable_numbers.h"
#include "client/animation_provider.h"

#include <utility>
#include "renderable_numbers.h"

RenderableNumbers::RenderableNumbers(
        std::shared_ptr<AnimationProvider> animation_provider):
        animation_provider(animation_provider) {
}

void RenderableNumbers::load_numbers() {
    for (char c = '0'; c <= '9'; ++c) {
        std::string key(1, c);
        animations[key] = std::move(animation_provider->make_animation(key));
    }
    animations[":"] = std::move(animation_provider->make_animation(":"));
    animations["|"] = std::move(animation_provider->make_animation("|"));
}

void RenderableNumbers::update(uint8_t number) {
    digits.clear();
    std::string str = std::to_string(number);
    for (char c : str) {
        digits.push_back(std::string(1, c));
    }
}

void RenderableNumbers::update_string(const std::string& str) {
    digits.clear();
    for (char c : str) {
        if (c >= '0' && c <= '9') {
            digits.push_back(std::string(1, c));
        } else if (c == ':') {
            digits.push_back(":");
        } else if (c == '|') {
            digits.push_back("|");
        }
    }
}


void RenderableNumbers::render(SDL2pp::Renderer& renderer, bool is_camera_enabled) {
    // x e y son en el extremo inferior izquierdo de la pantalla
    SDL2pp::Point screen_size = renderer.GetOutputSize();
    int x = 10;
    int y = screen_size.y - (66 * 0.5) - 10;        // TODO: hardcoded value based on texture
    int spacing_between_digits = 2;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    for (const auto& digit : digits) {
        if (animations.count(digit)) {
            animations[digit]->render(renderer, SDL2pp::Point(x, y), flip, 0, is_camera_enabled);
            // TODO: Hardcoded value based on texture
            x += (48 * 0.5) + spacing_between_digits;
        }
    }
}

RenderableNumbers::~RenderableNumbers() {}
