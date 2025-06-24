#ifndef CLIENT_RENDERABLES_RENDERABLE_HUD_BUY_GUNS_H
#define CLIENT_RENDERABLES_RENDERABLE_HUD_BUY_GUNS_H

#include <utility>
#include <vector>
#include <string>

#include "common/position.h"
#include "client/providers/animation_provider.h"
#include "client/renderables/hud/renderable_numbers.h"
#include "common/network/dtos/snapshot_dto.h"
#include <SDL2pp/Font.hh>

struct WeaponItem {
    std::string key;    // Tecla para comprar
    std::string name;   // Nombre del arma
    std::string price;  // Precio como string
};

struct AmmoItem {
    std::string key;    // Tecla para comprar
    std::string name;   // Tipo de munición
    std::string price;  // Precio como string
};

class RenderableHUDBuyGuns {
private:
    bool visible;
    SDL2pp::Font& font;
    int player_money;
    
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
    std::vector<WeaponItem> weapons_data;
    std::vector<AmmoItem> ammo_data;
    
    // Métodos privados para renderizado
    void setup_weapon_data();
    void render_background(SDL2pp::Renderer& renderer, const Position& screen_size);
    void render_weapons(SDL2pp::Renderer& renderer);
    void render_ammo(SDL2pp::Renderer& renderer, const Position& screen_size);
    void render_exit_option(SDL2pp::Renderer& renderer, const Position& screen_size);
    void render_key_number(SDL2pp::Renderer& renderer, const std::string& key, const Position& pos);
    void render_text(SDL2pp::Renderer& renderer, const std::string& text, 
                     const Position& pos, const SDL_Color& color);
    
    // Métodos auxiliares
    bool can_afford_weapon(const std::string& weapon_name);

public:
    RenderableHUDBuyGuns(std::shared_ptr<AnimationProvider> animation_provider, SDL2pp::Font& font);

    // Métodos para mostrar/ocultar
    void show() { visible = true; }
    void hide() { visible = false; }
    bool is_visible() const { return visible; }

    void update(const PrivatePlayerDTO& player_data);
    
    void render(SDL2pp::Renderer& renderer);
};

#endif
