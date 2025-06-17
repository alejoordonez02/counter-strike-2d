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
    // pointer(
    //         renderer,
    //         SDL2pp::Surface(DATA_PATH "/assets/gfx/pointer.bmp")
    //             .SetColorKey(true,
    //             SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 255, 0,
    //             255)) // Magenta
    //     ),

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
    textures["hud_symbols"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/hud_symbols.bmp");
    textures["hud_nums"] = std::make_shared<SDL2pp::Texture>(renderer, DATA_PATH "/assets/gfx/hud_nums.bmp");
    
    


    // ==== OTHER ======
    // pointer = SDL2pp::Texture(renderer, DATA_PATH "/assets/gfx/pointer.png");
    // counter_terrorist_1 = SDL2pp::Texture(renderer, DATA_PATH
    // "/assets/gfx/player/ct1.bmp"); terrorist_1 = SDL2pp::Texture(renderer,
    // DATA_PATH "/assets/gfx/player/t1.bmp");
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
