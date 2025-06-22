#ifndef SERVER_CONFIG_WORLD_CONFIG_H
#define SERVER_CONFIG_WORLD_CONFIG_H

#include "common/maploader.h"
#include "player_config.h"
#include "weapon_config.h"

struct WorldConfig {
    MapData map;
    PlayerConfig player;
    std::map<std::string, WeaponConfig> weapons;
    int rounds;
    float round_time;
    float time_out;
};

#endif
