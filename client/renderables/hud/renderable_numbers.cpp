#include "client/renderables/hud/renderable_numbers.h"
#include "client/providers/animation_provider.h"

#include <utility>
#include "renderable_numbers.h"

RenderableNumbers::RenderableNumbers(
        std::shared_ptr<AnimationProvider> animation_provider):
        animation_provider(animation_provider) {
            load_numbers();
}

void RenderableNumbers::load_numbers() {
    for (char c = '0'; c <= '9'; ++c) {
        std::string key(1, c);
        animations[key] = animation_provider->make_animation(key);
    }
    animations[":"] = animation_provider->make_animation(":");
    animations["|"] = animation_provider->make_animation("|");
}

void RenderableNumbers::update(uint number) {
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

Position RenderableNumbers::get_animation_size(){
    if (animations.empty()) {
        throw std::runtime_error("No animations loaded");
    }
    // Assuming all animations have the same size, return the size of the first one
    return animations.begin()->second->get_animation_size();
}


void RenderableNumbers::render(SDL2pp::Renderer& renderer, const Position& numbers_position, bool is_camera_enabled) {
    Position number_animation_size = get_animation_size();
    int x = numbers_position.x;
    int y = numbers_position.y;
    int spacing_between_digits = number_animation_size.x / 4;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    for (const auto& digit : digits) {
        if (animations.count(digit)) {
            animations[digit]->render(renderer, Position(x, y), flip, 0, is_camera_enabled);
            // next digit position
            x += number_animation_size.x + spacing_between_digits;
        }
    }
}

RenderableNumbers::~RenderableNumbers() {}
