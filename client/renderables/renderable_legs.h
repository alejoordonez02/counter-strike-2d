#ifndef RENDERABLE_LEGS_H
#define RENDERABLE_LEGS_H

#include "SDL2pp/SDL2pp.hh"

#include "../../common/snapshot.h"
#include "animation.h"

class RenderableLegs
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

    Animation* current_animation;
    std::unordered_map<std::string, Animation*> animations;


public:
    RenderableLegs(uint16_t player_id);
    
    void update(PlayerDTO& player);
    void render(SDL2pp::Renderer &renderer);

    void load_animation(const std::string& animation_name);
    ~RenderableLegs();
};

#endif