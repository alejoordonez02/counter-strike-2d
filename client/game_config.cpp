#include "client/game_config.h"


GameConfig::GameConfig(const std::string& path) {
    std::cout << "loading client config\n";
    YAML::Node yaml = YAML::LoadFile(path);

    load_window_config(yaml["window"]);
    load_fov_config(yaml["fov"]);
}

void GameConfig::load_fov_config(const YAML::Node& config) {
    fov.field_of_view_angle = config["field_of_view_angle"].as<uint>();
    fov.use_field_of_view = config["use_field_of_view"].as<bool>();
}


void GameConfig::load_window_config(const YAML::Node& config) {
    std::cout << "loading player config\n";
    window.window_width = config["window_width"].as<uint>();
    window.window_height = config["window_height"].as<uint>();
    window.use_fullscreen = config["use_fullscreen"].as<bool>();
    window.frame_rate = config["frame_rate"].as<uint>();
}

