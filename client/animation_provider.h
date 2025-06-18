#ifndef CLIENT_ANIMATION_PROVIDER_H
#define CLIENT_ANIMATION_PROVIDER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "client/renderables/animation.h"

struct AnimationPrototype {
    SDL2pp::Texture* texture;
    AnimationData data;
};

/*
 * Las animaciones pueden ser estaticas (un frame) o animadas (varios frames).
 */
class AnimationProvider {
    private:
    std::unordered_map<std::string, AnimationPrototype> animation_prototypes;

    public:
    AnimationProvider();
    std::unique_ptr<Animation> make_animation(
            const std::string& animation_name);

    void load_animations();
};

#endif
