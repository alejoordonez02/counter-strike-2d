#ifndef RENDERABLE_PLAYER_H
#define RENDERABLE_PLAYER_H

#include "SDL2pp/SDL2pp.hh"
#include <memory>


#include "../../common/snapshot.h"
#include "../animation_provider.h"
#include "animation.h"
#include "renderable_legs.h"

class RenderablePlayer
{
private:
    uint16_t player_id;
    bool is_terrorist;
    
    // Coordenadas del jugador: x,y
    SDL2pp::Point position;

    double facing_angle;

    // Estado del jugador (para animaciones y sonidos)
    bool is_shooting;
    bool was_hurt;
    bool is_walking;
    bool is_dead;

    WeaponType current_weapon;
    RenderableLegs legs;

    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    std::shared_ptr<AnimationProvider> animation_provider;


public:
    RenderablePlayer(uint16_t player_id, std::shared_ptr<AnimationProvider> animation_provider);
    
    void update(PlayerDTO& player);
    void render(SDL2pp::Renderer &renderer);

    void load_animation(const std::string& animation_name);
    ~RenderablePlayer();
};

#endif