#ifndef CLIENT_TEXTURE_PROVIDER_H
#define CLIENT_TEXTURE_PROVIDER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>

class TextureProvider {
    private:
    static std::unordered_map<std::string, std::shared_ptr<SDL2pp::Texture>>
            textures;

    TextureProvider();

    public:
    static std::shared_ptr<SDL2pp::Texture> get_texture(
            const std::string& texture_name);

    std::shared_ptr<SDL2pp::Texture> get_texture_from_file(
            SDL2pp::Renderer& renderer, const std::string& file_path);

    static void load_textures(SDL2pp::Renderer& renderer);
};

#endif  // TEXTURE_PROVIDER_H
