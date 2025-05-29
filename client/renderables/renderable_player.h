#ifndef RENDERABLE_PLAYER_H
#define RENDERABLE_PLAYER_H

#include "SDL2pp/SDL2pp.hh"

#include "../../common/snapshot.h"
#include "animation.h"

class RenderablePlayer
{
private:
    uint8_t player_id;

    // Coordenadas del jugador
    int16_t x;
    int16_t y;

    float facing_angle;

    // Estado del jugador (para animaciones y sonidos)
    bool is_shooting;
    bool was_hurt;
    bool is_walking;
    bool is_dead;

    WeaponType current_weapon;

    Animation animation;

public:
    RenderablePlayer(uint8_t player_id);
    
    void update(PlayerDTO& player);
    void render(SDL2pp::Renderer &renderer);

    ~RenderablePlayer();
};

#endif