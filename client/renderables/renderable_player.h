#ifndef CLIENT_RENDERABLES_RENDERABLE_PLAYER_H
#define CLIENT_RENDERABLES_RENDERABLE_PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Renderer.hh"
#include "client/providers/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/renderable_legs.h"
#include "client/renderables/renderable_gun.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/position.h"

class RenderablePlayer {
private:
    uint16_t player_id;
    bool is_terrorist;

    // Coordenadas del jugador: x,y
    Position position;

    double facing_angle;

    // Estado del jugador (para animaciones y sonidos)
    bool is_shooting;
    bool was_hurt;
    bool is_walking;
    bool is_dead;

    int fadeout_counter = 0;
    int fadeout_alpha = 255;
    bool is_fading_out = false;

    WeaponType current_weapon;
    RenderableLegs legs;
    RenderableGun gun;

    Animation* current_animation;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;

    std::shared_ptr<AnimationProvider> animation_provider;

public:
    RenderablePlayer(uint16_t player_id,
                     std::shared_ptr<AnimationProvider> animation_provider);

    /*
     * toda la data puede ser const, (si no se me queja el linter xd)
     * */
    void update(const PlayerDTO& player);

    void render(SDL2pp::Renderer& renderer);

    void load_animation(const std::string& animation_name);

    double calculate_facing_angle(float pos_x, float pos_y, float aim_x,
                                  float aim_y);

    void skip_frames(uint8_t frames_to_skip);

    ~RenderablePlayer();
};

#endif
