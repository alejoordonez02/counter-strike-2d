#include "client/animation_provider.h"
#include "client/renderables/animation.h"
#include "client/texture_provider.h"

void AnimationProvider::load_animations() {
// ====== PLAYERS =======
    animation_prototypes["terrorist_1_idle"] = {
            TextureProvider::get_texture("terrorist_1").get(),
            AnimationData{2, 1, false, 1, 0}};
    animation_prototypes["terrorist_2_idle"] = {
            TextureProvider::get_texture("terrorist_2").get(),
            AnimationData{2, 1, false, 1, 0}};
    animation_prototypes["terrorist_3_idle"] = {
            TextureProvider::get_texture("terrorist_3").get(),
            AnimationData{2, 1, false, 1, 0}};
    animation_prototypes["terrorist_4_idle"] = {
            TextureProvider::get_texture("terrorist_4").get(),
            AnimationData{2, 1, false, 1, 0}};
    animation_prototypes["terrorist_1_shooting"] = {
            TextureProvider::get_texture("terrorist_4").get(),
            AnimationData{2, 3, false, 1, 0}};
    animation_prototypes["legs"] = {TextureProvider::get_texture("legs").get(),
                                    AnimationData{4, 8, true, 5, 0}};

// ====== BACKGROUNDS ======
    animation_prototypes["background_dust"] = {TextureProvider::get_texture("background_dust").get(), AnimationData{1, 0, false, 0, 0}};
    animation_prototypes["background_sand1"] = {TextureProvider::get_texture("background_sand1").get(), AnimationData{1, 0, false, 0, 0}};
    animation_prototypes["background_aztec"] = {TextureProvider::get_texture("background_aztec").get(), AnimationData{1, 0, false, 0, 0}};
    
    // ======= TILES / BLOCKS ========
    animation_prototypes["solid1"] = {TextureProvider::get_texture("dust_tiles").get(), AnimationData{8, 9, false, 0, 0}};
    animation_prototypes["grass1"] = {TextureProvider::get_texture("dust_tiles").get(), AnimationData{8, 25, false, 0, 0}};
    animation_prototypes["plantspot"] = {TextureProvider::get_texture("dust_tiles").get(), AnimationData{8, 20, false, 0, 0}};
    animation_prototypes["grass2"] = {TextureProvider::get_texture("dust_tiles").get(), AnimationData{8, 26, false, 0, 0}};
    animation_prototypes["woodenbox1"] = {TextureProvider::get_texture("dust_tiles").get(), AnimationData{8, 65, false, 0, 0}};
    
}

// devuelve un nuevo puntero a la animacion
std::unique_ptr<Animation> AnimationProvider::make_animation(
        const std::string& animation_name) {
    auto it = animation_prototypes.find(animation_name);
    if (it == animation_prototypes.end()) {
        throw std::runtime_error("Animation not found: " + animation_name);
    }
    return std::make_unique<Animation>(*(it->second.texture), it->second.data);
}
