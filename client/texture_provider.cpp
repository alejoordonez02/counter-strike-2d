#include "client/texture_provider.h"

#include <memory>
#include "texture_provider.h"

// Proveedor de texturas a nivel global centralizado y compartido
// es estatico por lo tanto es único y global. vive durante toda la ejecución
// del programa. obviamente no es un singleton ya que no es necesario obtener su
// instancia

// al tener un shared_ptr cuando nadie mas tenga lo este utilizando
// se liberará la textura automaticamente.

// si bien es mutable, ya que su metodo load_textures carga las texturas, pero
// estas son globales

// Aqui se le dice al compilador que reserve memoria para este objeto estatico:
std::unordered_map<std::string, std::shared_ptr<SDL2pp::Texture>>
        TextureProvider::textures;

TextureProvider::TextureProvider() {}

void TextureProvider::load_textures(SDL2pp::Renderer& renderer) {
    // ==== PLAYERS ======
    textures["terrorist_1"] = std::make_shared<SDL2pp::Texture>(
            renderer, DATA_PATH "/assets/gfx/player/t1.bmp");
    textures["terrorist_2"] = std::make_shared<SDL2pp::Texture>(
            renderer, DATA_PATH "/assets/gfx/player/t2.bmp");
    textures["terrorist_3"] = std::make_shared<SDL2pp::Texture>(
            renderer, DATA_PATH "/assets/gfx/player/t3.bmp");
    textures["terrorist_4"] = std::make_shared<SDL2pp::Texture>(
            renderer, DATA_PATH "/assets/gfx/player/t4.bmp");
    textures["legs"] = std::make_shared<SDL2pp::Texture>(
            renderer, DATA_PATH "/assets/gfx/player/legs.bmp");
            
    // ==== BACKGROUNDS ======
    textures["background_sand1"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/backgrounds/sand1.jpg");
    textures["background_dust"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/backgrounds/dust.png");
    textures["background_aztec"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/backgrounds/aztec.png");
    textures["background_nuke"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/backgrounds/nuke.png");
            
    // ==== BLOCKS ======
    textures["dust_tiles"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/tiles/dust.bmp");
    textures["aztect_tiles"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/tiles/aztec.bmp");
    textures["embrador_tiles"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/tiles/embrador.bmp");
    
    
    
    // ==== HUD ======
    // Cargar hud_symbols con fondo negro como transparente
    SDL2pp::Surface hud_symbols_surface(DATA_PATH "/assets/gfx/hud_symbols.bmp");
    hud_symbols_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0)); // Negro
    textures["hud_symbols"] = std::make_shared<SDL2pp::Texture>(renderer, hud_symbols_surface);
    
    SDL2pp::Surface hud_numbers_surface(DATA_PATH "/assets/gfx/hud_nums.bmp");
    hud_numbers_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0)); // Negro
    textures["hud_nums"] = std::make_shared<SDL2pp::Texture>(renderer, hud_numbers_surface);
    
    
    // ==== GUNS ======
    SDL2pp::Surface held_bomb_surface(DATA_PATH "/assets/gfx/weapons/bomb.bmp");
    held_bomb_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["held_bomb"] = std::make_shared<SDL2pp::Texture>(renderer, held_bomb_surface);

    SDL2pp::Surface held_knife_surface(DATA_PATH "/assets/gfx/weapons/knife.bmp");
    held_knife_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["held_knife"] = std::make_shared<SDL2pp::Texture>(renderer, held_knife_surface);

    SDL2pp::Surface held_glock_surface(DATA_PATH "/assets/gfx/weapons/glock.bmp");
    held_glock_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["held_glock"] = std::make_shared<SDL2pp::Texture>(renderer, held_glock_surface);
    
    SDL2pp::Surface held_ak47_surface(DATA_PATH "/assets/gfx/weapons/ak47.bmp");
    held_ak47_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["held_ak47"] = std::make_shared<SDL2pp::Texture>(renderer, held_ak47_surface);
    
    SDL2pp::Surface held_m3_surface(DATA_PATH "/assets/gfx/weapons/m3.bmp");
    held_m3_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["held_m3"] = std::make_shared<SDL2pp::Texture>(renderer, held_m3_surface);

    SDL2pp::Surface held_awp_surface(DATA_PATH "/assets/gfx/weapons/awp.bmp");
    held_awp_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["held_awp"] = std::make_shared<SDL2pp::Texture>(renderer, held_awp_surface);


    SDL2pp::Surface bomb_surface(DATA_PATH "/assets/gfx/weapons/bomb_d.bmp");
    bomb_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["bomb"] = std::make_shared<SDL2pp::Texture>(renderer, bomb_surface);

    SDL2pp::Surface glock_surface(DATA_PATH "/assets/gfx/weapons/glock_d.bmp");
    glock_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["glock"] = std::make_shared<SDL2pp::Texture>(renderer, glock_surface);
    
    SDL2pp::Surface ak47_surface(DATA_PATH "/assets/gfx/weapons/ak47_d.bmp");
    ak47_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["ak47"] = std::make_shared<SDL2pp::Texture>(renderer, ak47_surface);
    
    SDL2pp::Surface m3_surface(DATA_PATH "/assets/gfx/weapons/m3_d.bmp");
    m3_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["m3"] = std::make_shared<SDL2pp::Texture>(renderer, m3_surface);

    SDL2pp::Surface awp_surface(DATA_PATH "/assets/gfx/weapons/awp_d.bmp");
    awp_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["awp"] = std::make_shared<SDL2pp::Texture>(renderer, awp_surface);
    

    SDL2pp::Surface tilesheet_2_surface(DATA_PATH "/../resources/weapons/tilesheet_2.png");
    tilesheet_2_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 255, 255, 255));
    textures["tilesheet_2"] = std::make_shared<SDL2pp::Texture>(renderer, tilesheet_2_surface);

    // ==== EFFECTS ======
    // modular color a uno amarillo

    SDL2pp::Surface flare3_surface(DATA_PATH "/assets/gfx/flare3.bmp");
    flare3_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["flare3"] = std::make_shared<SDL2pp::Texture>(renderer, flare3_surface);
    textures["flare3"]->SetColorMod(255, 255, 0);
    textures["flare3"]->SetAlphaMod(128); // 128 es 50% opacidad
    
    SDL2pp::Surface knifeslash_surface(DATA_PATH "/assets/gfx/knifeslash.bmp");
    knifeslash_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["knifeslash"] = std::make_shared<SDL2pp::Texture>(renderer, knifeslash_surface);
    textures["knifeslash"]->SetAlphaMod(128); // 128 es 50% opacidad
    
    // ==== OTHER ======
    SDL2pp::Surface decals_surface(DATA_PATH "/assets/gfx/decals.bmp");
    decals_surface.SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 0, 0, 0));
    textures["decals"] = std::make_shared<SDL2pp::Texture>(renderer, decals_surface);
    textures["decals"]->SetColorMod(255, 255, 0);
    textures["decals"]->SetAlphaMod(128); // 128 es 50% opacidad

    // pointer = SDL2pp::Texture(renderer, DATA_PATH "/assets/gfx/pointer.png");
    // counter_terrorist_1 = SDL2pp::Texture(renderer, DATA_PATH
    // "/assets/gfx/player/ct1.bmp"); terrorist_1 = SDL2pp::Texture(renderer,
    // DATA_PATH "/assets/gfx/player/t1.bmp");

    // pointer(
    //         renderer,
    //         SDL2pp::Surface(DATA_PATH "/assets/gfx/pointer.bmp")
    //             .SetColorKey(true,
    //             SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 255, 0,
    //             255)) // Magenta
    //     ),
}

std::shared_ptr<SDL2pp::Texture> TextureProvider::get_texture(
        const std::string& texture_name) {
    if (textures.find(texture_name) == textures.end()) {
        throw std::runtime_error("Texture not found: " + texture_name);
    }
    // verificar que tenga un alto y largo validos
    std::shared_ptr<SDL2pp::Texture> texture = textures[texture_name];
    if (texture->GetWidth() == 0 || texture->GetHeight() == 0) {
        std::cerr << "Error: textura no cargada correctamente" << std::endl;
    }
    return texture;
}

std::shared_ptr<SDL2pp::Texture> TextureProvider::get_texture_from_file(
        SDL2pp::Renderer& renderer, const std::string& file_path) {
    auto texture = std::make_shared<SDL2pp::Texture>(renderer, file_path);
    if (texture->GetWidth() == 0 || texture->GetHeight() == 0) {
        std::cerr << "Error: textura no cargada correctamente desde el archivo "
                  << file_path << std::endl;
        return nullptr;
    }
    return texture;
}
