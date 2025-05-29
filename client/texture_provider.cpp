// NOTE: la idea sería cargar todas las texturas durante la inicializacion
// se cargará una sola vez y será compartida entre todos los hilos (shared ptr?)
// para evitar copias y demás

#include "texture_provider.h"

TextureProvider::TextureProvider(SDL2pp::Renderer & renderizador): 
    renderer(renderizador),
    // pointer(renderer, DATA_PATH "/assets/gfx/pointer.bmp"),
    pointer(
            renderer,
            SDL2pp::Surface(DATA_PATH "/assets/gfx/pointer.bmp")
                .SetColorKey(true, SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 255, 0, 255)) // Magenta
        ),
    counter_terrorist_1(renderer, DATA_PATH "/assets/gfx/player/ct1.bmp"),
    terrorist_1(renderer, DATA_PATH "/assets/gfx/player/t1.bmp")
    {}

    

void TextureProvider::load_textures() {
    // cargar texturas
    
    // pointer = SDL2pp::Texture(renderer, DATA_PATH "/assets/gfx/pointer.png");
    // counter_terrorist_1 = SDL2pp::Texture(renderer, DATA_PATH "/assets/gfx/player/ct1.bmp");
    // terrorist_1 = SDL2pp::Texture(renderer, DATA_PATH "/assets/gfx/player/t1.bmp");
}

SDL2pp::Texture* TextureProvider::get_texture_pointer(){
    return &pointer;
}


SDL2pp::Texture* TextureProvider::get_texture_terrorist(){
    return &counter_terrorist_1;
}


// SDL2pp::Texture* TextureProvider::get_texture(const std::string& texture_name){
    
// }
