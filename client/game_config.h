#ifndef CLIENT_GAME_CONFIG_H
#define CLIENT_GAME_CONFIG_H

#include <string>
#include <iostream>

#include <yaml-cpp/yaml.h>

struct WindowConfig {
  uint window_width;
  uint window_height;
  bool use_fullscreen;
  uint frame_rate;
};

struct FOVConfig {
    uint field_of_view_angle;
    bool use_field_of_view;
};


struct GunsData{
    std::string name;
    uint price;
};
struct GunsConfig {
    std::unordered_map<std::string, GunsData> guns;
    int primary_ammo_price;
    int secondary_ammo_price;
};


class GameConfig {
    private:
        void load_fov_config(const YAML::Node& config);
        void load_window_config(const YAML::Node& config);
        void load_guns_config(const YAML::Node& config);

    public:
        GameConfig(const std::string& path);

        WindowConfig window;
        FOVConfig fov;
        GunsConfig guns_config;

};

#endif