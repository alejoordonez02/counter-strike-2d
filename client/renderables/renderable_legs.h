#ifndef RENDERABLE_LEGS_H
#define RENDERABLE_LEGS_H

#include "SDL2pp/SDL2pp.hh"
#include <memory>


#include "../../common/snapshot.h"
#include "animation.h"
#include "../animation_provider.h"

class RenderableLegs
{
private:
    SDL2pp::Point position;
    double facing_angle;


    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    std::shared_ptr<AnimationProvider> animation_provider;


public:
    RenderableLegs(std::shared_ptr<AnimationProvider> animation_provider);
    
    void update(const SDL2pp::Point& position, double facing_angle);
    void render(SDL2pp::Renderer &renderer);

    void load_animation(const std::string& animation_name);
    ~RenderableLegs();
};

#endif