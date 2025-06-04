#ifndef ANIMATION_PROVIDER_H
#define ANIMATION_PROVIDER_H

#include <string>
#include <unordered_map>

#include "client/renderables/animation.h"




class AnimationProvider {
private:
    static std::unordered_map<std::string, AnimationData> frames_data;

    AnimationProvider() {}


public:
    static const AnimationData& get_animation_data(const std::string& name);

    static void load_animations();
};

#endif
