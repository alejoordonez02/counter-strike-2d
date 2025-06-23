#ifndef CLIENT_ANIMATION_PROVIDER_H
#define CLIENT_ANIMATION_PROVIDER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <iostream>

#include <yaml-cpp/yaml.h>

#include "client/renderables/animation.h"
#include "client/providers/texture_provider.h"

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
    void load_animation_yaml(const std::string& yaml_path);
    AnimationData parse_animation_data(const YAML::Node& node);
    std::unique_ptr<Animation> make_animation(
        const std::string& animation_name);

    void load_other_sprites();
    void load_sprites_from_yaml();
};

#endif
