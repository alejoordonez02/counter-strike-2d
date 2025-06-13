#ifndef CLIENT_RENDERABLES_RENDERABLE_PLAYER_H
#define CLIENT_RENDERABLES_RENDERABLE_PLAYER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2pp/Point.hh"
#include "SDL2pp/Renderer.hh"
#include "client/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/renderables/renderable_legs.h"
#include "common/snapshot.h"

class RenderablePlayer {
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
    RenderablePlayer(uint16_t player_id,
                     std::shared_ptr<AnimationProvider> animation_provider);

    void update(PlayerData& player);
    void render(SDL2pp::Renderer& renderer);

    void load_animation(const std::string& animation_name);

    double calculate_facing_angle(int pos_x, int pos_y, int aim_x, int aim_y);
    ~RenderablePlayer();
};

#endif
