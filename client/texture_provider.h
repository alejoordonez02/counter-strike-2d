#ifndef TEXTURE_PROVIDER_H
#define TEXTURE_PROVIDER_H

#include <SDL2pp/SDL2pp.hh>

class TextureProvider {
    private:
        SDL2pp::Renderer& renderer;
        
        SDL2pp::Texture pointer;
        SDL2pp::Texture counter_terrorist_1;
        SDL2pp::Texture terrorist_1;

        // static std::unordered_map<std::string, SDL2pp::Texture> textures;


    public:
        TextureProvider(SDL2pp::Renderer & renderer);
        
        void load_textures();

        // SDL2pp::Texture* get_texture(const std::string& texture_name);

        SDL2pp::Texture* get_texture_pointer();

        SDL2pp::Texture* get_texture_terrorist();
};

#endif // TEXTURE_PROVIDER_H