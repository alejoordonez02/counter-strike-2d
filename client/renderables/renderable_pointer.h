#ifndef CLIENT_RENDERABLES_RENDERABLE_POINTER_H
#define CLIENT_RENDERABLES_RENDERABLE_POINTER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include "client/providers/animation_provider.h"

class RenderablePointer {
    private:
    int x, y;
    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    public:
    explicit RenderablePointer(std::shared_ptr<AnimationProvider> animation_provider);

    void update(bool is_attacking);

    void render(SDL2pp::Renderer& renderer);
};

#endif  // CLIENT_RENDERABLES_RENDERABLE_POINTER_H
