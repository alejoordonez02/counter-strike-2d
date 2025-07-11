#ifndef CLIENT_RENDERABLES_RENDERABLE_NUMBERS_H
#define CLIENT_RENDERABLES_RENDERABLE_NUMBERS_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Point.hh"
#include "SDL2pp/Renderer.hh"
#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"

class RenderableNumbers {
    private:

    std::shared_ptr<AnimationProvider> animation_provider;

    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
    std::vector<std::string> digits;

    public:
    RenderableNumbers(std::shared_ptr<AnimationProvider> animation_provider);

    void render(SDL2pp::Renderer& renderer, const Position& number_position, bool is_camera_enabled);

    void load_numbers();

    void update(uint number);

    void update_string(const std::string& str);

    Position get_animation_size();

    ~RenderableNumbers();
};

#endif
