#include "client/game_config.h"


GameConfig::GameConfig(const std::string& path) {
    std::cout << "LOG: loading client config\n";
    YAML::Node yaml = YAML::LoadFile(path);
    
    load_window_config(yaml["window"]);
    load_fov_config(yaml["fov"]);
    load_sfx_config(yaml["sfx"]);
    
    YAML::Node yaml_server = YAML::LoadFile("config/server-config.yaml");
    load_guns_config(yaml_server["world"]);
}

void GameConfig::load_window_config(const YAML::Node& config) {
    std::cout << "LOG: loading player config\n";
    window.window_width = config["window_width"].as<uint>();
    window.window_height = config["window_height"].as<uint>();
    window.use_fullscreen = config["use_fullscreen"].as<bool>();
    window.frame_rate = config["frame_rate"].as<uint>();
}

void GameConfig::load_fov_config(const YAML::Node& config) {
    fov.field_of_view_angle = config["field_of_view_angle"].as<uint>();
    fov.use_field_of_view = config["use_field_of_view"].as<bool>();
}

void GameConfig::load_sfx_config(const YAML::Node& config) {
    sfx.use_sound = config["use_sound"].as<bool>();
    sfx.use_music = config["use_music"].as<bool>();
    sfx.sound_volume = config["sound_volume"].as<int>();
    sfx.music_volume = config["music_volume"].as<int>();
}

void GameConfig::load_guns_config(const YAML::Node& config) {
    std::cout << "LOG: loading guns config\n";
    guns_config.primary_ammo_price = config["ammo"]["primary_ammo_price"].as<int>();
    guns_config.secondary_ammo_price = config["ammo"]["secondary_ammo_price"].as<int>();

    for (const auto& gun : config["weapons"]) {
        GunsData data;
        std::string gun_name = gun.first.as<std::string>();
        data.name = gun_name;
        data.price = gun.second["cost"].as<uint>();
        guns_config.guns.emplace(gun_name, data);
    }
}

