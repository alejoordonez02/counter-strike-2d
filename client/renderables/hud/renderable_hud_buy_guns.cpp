#include "client/renderables/hud/renderable_hud_buy_guns.h"

RenderableHUDBuyGuns::RenderableHUDBuyGuns(std::shared_ptr<AnimationProvider> animation_provider, SDL2pp::Font& font, const GameConfig& game_config):
font(font), visible(true) {  // Por defecto oculto
    // Cargar animaciones de armas
    animations["glock"] = animation_provider->make_animation("glock");
    animations["ak47"] = animation_provider->make_animation("ak47");
    animations["m3"] = animation_provider->make_animation("m3");
    animations["awp"] = animation_provider->make_animation("awp");
    
    // Inicializar datos de armas
    setup_weapon_data(game_config);
}


void RenderableHUDBuyGuns::setup_weapon_data(const GameConfig& game_config) {
    // Configurar datos de armas (tecla, nombre, precio)
    // std::unordered_map<std::string, GunsConfig>

    weapons_data = {
        {"1", game_config.guns_config.guns.at("Glock").name, "$" + std::to_string(game_config.guns_config.guns.at("Glock").price)},
        {"2", game_config.guns_config.guns.at("Ak47").name, "$" + std::to_string(game_config.guns_config.guns.at("Ak47").price)},
        {"3", game_config.guns_config.guns.at("M3").name, "$" + std::to_string(game_config.guns_config.guns.at("M3").price)},
        {"4", game_config.guns_config.guns.at("Awp").name, "$" + std::to_string(game_config.guns_config.guns.at("Awp").price)},
    };
    
    // Configurar datos de munición
    ammo_data = {
        {"5", "Primaria", "$" + std::to_string(game_config.guns_config.primary_ammo_price)},
        {"6", "Secundaria", "$" + std::to_string(game_config.guns_config.secondary_ammo_price)}
    };
}

void RenderableHUDBuyGuns::update(const PrivatePlayerDTO& player_data) {
    // Actualizar dinero del jugador para mostrar qué puede comprar
    player_money = player_data.total_money;
}


void RenderableHUDBuyGuns::render(SDL2pp::Renderer& renderer) {
    if (!visible) return;
    
    Position screen_size = Position(renderer.GetOutputSize().x, renderer.GetOutputSize().y);
    
    // Renderizar fondo semi-transparente
    render_background(renderer, screen_size);
    
    // Renderizar armas del lado izquierdo
    render_weapons(renderer);
    
    // Renderizar municiones del lado derecho  
    render_ammo(renderer, screen_size);
    
    // Renderizar opción de salir
    render_exit_option(renderer, screen_size);
}

int margin = 50;
int padding = 30;

void RenderableHUDBuyGuns::render_background(SDL2pp::Renderer& renderer, const Position& screen_size) {
    // Fondo semi-transparente que ocupa la mayor parte de la pantalla
    SDL2pp::Rect background_rect(
        margin, 
        margin, 
        screen_size.x - 2 * margin, 
        screen_size.y - 2 * margin
    );
    
    renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer.SetDrawColor(0, 0, 0, 250); // Negro semi-transparente
    renderer.FillRect(background_rect);
}

void RenderableHUDBuyGuns::render_weapons(SDL2pp::Renderer& renderer) {
    // empieza de la esquina superior izquierda dentro del rectangulo
    int start_x = padding + margin;
    int start_y = padding + margin;
    Position icon_size = animations["ak47"].get()->get_animation_size();
    
    for (size_t i = 0; i < weapons_data.size(); ++i) {
        const auto& weapon = weapons_data[i];
        int y_pos = start_y + (i * icon_size.y + i * padding);
        
        // Renderizar número de tecla
        render_key_number(renderer, weapon.key, Position(start_x, y_pos));
        
        // Renderizar icono del arma
        std::string weapon_name = weapon.name;
        std::transform(weapon_name.begin(), weapon_name.end(), weapon_name.begin(), ::tolower);
        if (animations.find(weapon_name) != animations.end()) {
            Position icon_pos(start_x + icon_size.x, y_pos);
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            animations[weapon_name]->render(renderer, icon_pos, flip, 0, false);
        }
        
        // Renderizar nombre del arma
        Position name_pos(start_x + (icon_size.x * 2) + padding, y_pos - padding+10);
        render_text(renderer, weapon.name, name_pos, SDL_Color{255, 255, 255, 255});
        
        // Renderizar precio del arma
        Position price_pos(start_x + (icon_size.x * 2) + padding, y_pos);
        // Verde si puede comprar, rojo si no
        SDL_Color price_color = can_afford_weapon(weapon.name) ? 
            SDL_Color{0, 255, 0, 255} : SDL_Color{255, 0, 0, 255}; 
        render_text(renderer, weapon.price, price_pos, price_color);
    }
}

void RenderableHUDBuyGuns::render_ammo(SDL2pp::Renderer& renderer, const Position& screen_size) {
    Position icon_size = animations["ak47"].get()->get_animation_size();
    int start_x = screen_size.x/2 + icon_size.x;  // Lado derecho
    int start_y = padding + margin;
    
    for (size_t i = 0; i < ammo_data.size(); ++i) {
        const auto& ammo = ammo_data[i];
        int y_pos = start_y + (i * icon_size.y + i * padding);
        
        // Renderizar número de tecla
        render_key_number(renderer, ammo.key, Position(start_x, y_pos));
        
        // Renderizar nombre de munición (sin icono)
        Position name_pos(start_x + icon_size.x, y_pos - padding+10);
        render_text(renderer, "Municion " + ammo.name, name_pos, SDL_Color{255, 255, 255, 255});
        
        // Renderizar precio de munición
        Position price_pos(start_x + padding, y_pos);
        render_text(renderer, ammo.price, price_pos, SDL_Color{0, 255, 0, 255});
    }
}

void RenderableHUDBuyGuns::render_exit_option(SDL2pp::Renderer& renderer, const Position& screen_size) {
    Position icon_size = animations["ak47"].get()->get_animation_size();
    // Esquina inferior derecha
    int x = screen_size.x / 2 + icon_size.x;
    int y = screen_size.y - (margin + padding);
    
    // Renderizar número de tecla para salir
    render_key_number(renderer, "0", Position(x, y));
    
    // Renderizar texto "Salir"
    Position text_pos(x + icon_size.x, y);
    render_text(renderer, "Salir", text_pos, SDL_Color{255, 255, 255, 255});
}

void RenderableHUDBuyGuns::render_key_number(SDL2pp::Renderer& renderer, const std::string& key, const Position& pos) {
    // Fondo rectangular para el número (relleno)
    int radius = 15;
    SDL2pp::Rect key_bg(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
    
    renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer.SetDrawColor(100, 100, 100, 200); // Gris semi-transparente
    renderer.FillRect(key_bg);
    
    // Borde del rectangulo (solid)
    renderer.SetDrawColor(255, 255, 255, 255); // Blanco
    renderer.DrawRect(key_bg);
    
    // Número centrado
    Position text_pos(pos.x - 8, pos.y - 8);
    render_text(renderer, key, text_pos, SDL_Color{255, 255, 255, 255});
}

void RenderableHUDBuyGuns::render_text(SDL2pp::Renderer& renderer, const std::string& text, 
                                      const Position& pos, const SDL_Color& color) {
    SDL2pp::Surface text_surface = font.RenderText_Blended(text, color);
    SDL2pp::Texture text_texture(renderer, text_surface);
    
    SDL2pp::Rect dst(pos.x, pos.y, text_texture.GetWidth(), text_texture.GetHeight());
    renderer.Copy(text_texture, SDL2pp::NullOpt, dst);
}


bool RenderableHUDBuyGuns::can_afford_weapon(const std::string& weapon_name) {
    // Precios hardcodeados por ahora (deberían venir de configuración)
    if (weapon_name == "Glock") return player_money >= 200;
    if (weapon_name == "AK47") return player_money >= 2500;
    if (weapon_name == "M3") return player_money >= 1700;
    if (weapon_name == "AWP") return player_money >= 4750;
    return false;
}


