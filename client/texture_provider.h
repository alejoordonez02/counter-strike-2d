#ifndef TEXTURE_PROVIDER_H
#define TEXTURE_PROVIDER_H

#include <SDL2pp/SDL2pp.hh>

class TextureProvider {
    private:
        SDL2pp::Renderer& renderer;
        SDL2pp::Texture mira;

    public:
        TextureProvider(SDL2pp::Renderer & renderer);
        SDL2pp::Texture * get_texture();
};

#endif // TEXTURE_PROVIDER_H