#ifndef SERVER_GAME_CONFIG_H
#define SERVER_GAME_CONFIG_H

#include <yaml-cpp/yaml.h>

#include <map>
#include <string>

#include "common/map_name.h"
#include "common/maploader.h"
#include "loop_config.h"
#include "player_config.h"
#include "snapshot_dto.h"
#include "weapon_config.h"
#include "world_config.h"

class GameConfig {
private:
    void load_loop_config(YAML::Node config);
    MapData load_map_config(MapName map_name);
    void load_world_config(YAML::Node config, MapName map);
    PlayerConfig load_player_config(YAML::Node config);
    std::map<WeaponName, WeaponConfig> load_weapon_configs(YAML::Node config);

public:
    LoopConfig loop;
    MapData map;
    WorldConfig world;

    GameConfig(const std::string& path, MapName map);
};

#endif
