#ifndef SERVER_GAME_CONFIG_H
#define SERVER_GAME_CONFIG_H

#include <yaml-cpp/yaml.h>

#include <map>
#include <string>

#include "common/map_name.h"
#include "common/maploader.h"
#include "loop_config.h"
#include "weapon_config.h"
#include "world_config.h"

class GameConfig {
public:
    LoopConfig loop;
    WorldConfig world;
    MapData map;
    std::map<std::string, WeaponConfig> weapons;

    static GameConfig from_yaml(const std::string& path, MapName map);
};

#endif
