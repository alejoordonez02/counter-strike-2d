#include "client/providers/animation_provider.h"

AnimationProvider::AnimationProvider(){
        load_sprites_from_yaml();
        load_other_sprites();
}

void AnimationProvider::load_animation_yaml(const std::string& yaml_path) {
    YAML::Node config = YAML::LoadFile(yaml_path);
    std::string texture_name = config["texture_name"].as<std::string>();
    int columns_of_sprite_sheet = config["columns"].as<int>();
    std::cout << "LOG: Reading texture_name: " << texture_name << std::endl;

    SDL2pp::Texture* texture = TextureProvider::get_texture(texture_name).get();
    if (!texture) {
        throw std::runtime_error("Texture not found: " + texture_name);
    }
    for (const auto& sprite_node : config["sprite_data"]) {
        std::string name = sprite_node["name"].as<std::string>();
        AnimationData data = parse_animation_data(sprite_node, columns_of_sprite_sheet);
        animation_prototypes[name] = {texture, data};
    }
}

AnimationData AnimationProvider::parse_animation_data(const YAML::Node& node, int columns_of_sprite_sheet) {
    AnimationData data;
    data.columns = columns_of_sprite_sheet;
    data.frames = node["frames"].as<int>();
    data.is_animated = node["is_animated"].as<bool>();
    data.steps = node["steps"] ? node["steps"].as<int>() : 0;
    data.size_width = node["size_width"] ? node["size_width"].as<int>() : 0;
    data.size_height = node["size_height"] ? node["size_height"].as<int>() : 0;
    data.modify_size = node["modify_size"] ? node["modify_size"].as<float>() : 0.0f;
    return data;
}


void AnimationProvider::load_sprites_from_yaml() {
    // carga todos los archivos .yaml dentro de "client/spritesheet_data"
    std::string animation_data_dir = "client/providers/spritesheet_data";
    for (const auto& entry : std::filesystem::directory_iterator(animation_data_dir)) {
        if (entry.path().extension() == ".yaml") {
            load_animation_yaml(entry.path().string());
        }
    }
}



void AnimationProvider::load_other_sprites() {
    // muy especificos para ser cargados mediante un yaml
    // Resulta mas practico de esta manera
    

    // ====== PLAYERS =======
    // Terrorists
    for (int i = 1; i <= 4; ++i) {
        std::string base = "terrorist_" + std::to_string(i);
        animation_prototypes[base + "_holding_knife"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 0, false}};
        animation_prototypes[base + "_idle"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 1, false}};
        animation_prototypes[base + "_placing_bomb"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 2, false}};
        animation_prototypes[base + "_holding_pistol"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 3, false}};
        animation_prototypes[base + "_holding_rifle"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 5, false}};
    }
    // Counter-Terrorists
    for (int i = 1; i <= 4; ++i) {
        std::string base = "counter_terrorist_" + std::to_string(i);
        animation_prototypes[base + "_holding_knife"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 0, false}};
        animation_prototypes[base + "_idle"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 1, false}};
        animation_prototypes[base + "_placing_bomb"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 2, false}};
        animation_prototypes[base + "_holding_pistol"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 3, false}};
        animation_prototypes[base + "_holding_rifle"] = {TextureProvider::get_texture(base).get(), AnimationData{2, 5, false}};
    }
    animation_prototypes["legs"] = {TextureProvider::get_texture("legs").get(), AnimationData{4, 8, true, 5, 0}};


    // ====== GUNS ======
    animation_prototypes["held_bomb"] = {TextureProvider::get_texture("held_bomb").get(), AnimationData{1, 0, false}};
    animation_prototypes["held_knife"] = {TextureProvider::get_texture("held_knife").get(), AnimationData{1, 0, false}};
    animation_prototypes["held_glock"] = {TextureProvider::get_texture("held_glock").get(), AnimationData{1, 0, false}};
    animation_prototypes["held_ak47"] = {TextureProvider::get_texture("held_ak47").get(), AnimationData{1, 0, false}};
    animation_prototypes["held_m3"] = {TextureProvider::get_texture("held_m3").get(), AnimationData{1, 0, false}};
    animation_prototypes["held_awp"] = {TextureProvider::get_texture("held_awp").get(), AnimationData{1, 0, false}};
    
    animation_prototypes["bomb"] = {TextureProvider::get_texture("bomb").get(), AnimationData{1, 0, false}};
    animation_prototypes["glock"] = {TextureProvider::get_texture("tilesheet_2").get(), AnimationData{4, 0, false}};
    animation_prototypes["ak47"] = {TextureProvider::get_texture("tilesheet_2").get(), AnimationData{4, 1, false}};
    animation_prototypes["m3"] = {TextureProvider::get_texture("tilesheet_2").get(), AnimationData{4, 2, false}};
    animation_prototypes["awp"] = {TextureProvider::get_texture("tilesheet_2").get(), AnimationData{4, 3, false}};

    // ====== EFFECTS ======
    animation_prototypes["flare3"] = {TextureProvider::get_texture("flare3").get(), AnimationData{2, 2, true, 0, 0, 0, 0.5}};
    animation_prototypes["knifeslash"] = {TextureProvider::get_texture("knifeslash").get(), AnimationData{1, 0, false, 0, 0, 0, 0.5}};
    
    animation_prototypes["decals"] = {TextureProvider::get_texture("decals").get(), AnimationData{18, 13, false}};

    // ====== BACKGROUNDS ======
    animation_prototypes["background_dust"] = {TextureProvider::get_texture("background_dust").get(), AnimationData{1, 0, false, 0}};
    animation_prototypes["background_sand1"] = {TextureProvider::get_texture("background_sand1").get(), AnimationData{1, 0, false, 0}};
    animation_prototypes["background_aztec"] = {TextureProvider::get_texture("background_aztec").get(), AnimationData{1, 0, false, 0}};
    animation_prototypes["background_nuke"] = {TextureProvider::get_texture("background_nuke").get(), AnimationData{1, 0, false, 0}};
    

    // ====== POINTERS ======
    animation_prototypes["green_pointer"] = {TextureProvider::get_texture("pointer").get(), AnimationData{2, 0, false, 0, 0, 0, 0.5}};
    animation_prototypes["red_pointer"] = {TextureProvider::get_texture("pointer").get(), AnimationData{2, 1, false, 0, 0, 0, 0.5}};
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
