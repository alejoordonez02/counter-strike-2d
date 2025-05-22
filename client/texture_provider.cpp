// NOTE: la idea sería cargar todas las texturas durante la inicializacion
// se cargará una sola vez y será compartida entre todos los hilos (shared ptr?)
// para evitar copias y demás

#include "texture_provider.h"

TextureProvider::TextureProvider(SDL2pp::Renderer & caca): 
    renderer(caca), 
    mira(renderer, DATA_PATH "/assets/gfx/pointer.bmp"){

        
}

SDL2pp::Texture* TextureProvider::get_texture(){
    return &mira;
}
