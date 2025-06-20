#include "server/config/game_config.h"

#include <stdexcept>

GameConfig GameConfig::from_yaml(const std::string& path, MapName map) {
    YAML::Node yaml = YAML::LoadFile(path);
    GameConfig config;

    auto s = yaml["server"];
    config.loop.tick_rate = s["tick_rate"].as<int>();
    config.loop.commands_per_tick = s["commands_per_tick"].as<int>();

    auto w = yaml["world"];
    config.world.rounds = w["rounds"].as<int>();
    config.world.round_time = w["round_time"].as<float>();
    config.world.time_out = w["time_out"].as<float>();
    config.world.player_max_velocity = w["player_max_velocity"].as<float>();
    config.world.player_acceleration = w["player_acceleration"].as<float>();
    config.world.player_radius = w["player_radius"].as<float>();
    config.world.player_starting_money = w["player_starting_money"].as<int>();
    config.world.player_max_health = w["player_max_health"].as<int>();

    auto weapons = yaml["weapons"];
    for (auto w : weapons) {
        std::string name = w.first.as<std::string>();
        auto wconf = w.second;
        WeaponConfig weapon_config;
        weapon_config.damage = wconf["damage"].as<int>();
        weapon_config.ammo = wconf["ammo"].as<int>();
        weapon_config.accuracy = wconf["accuracy"].as<float>();
        weapon_config.range = wconf["range"].as<float>();
        weapon_config.fire_delay = wconf["fire_delay"].as<float>();
        weapon_config.cost = wconf["cost"].as<int>();
        weapon_config.ammo_cost = wconf["ammo_cost"].as<int>();
        config.weapons[name] = weapon_config;
    }

    /*
     * No están los mapas definidos todavía así que uso el mismo para todos
     * */
    std::string map_file;
    switch (map) {
        case MapName::DUST:
            map_file = "tests/client/prueba_mapa_mod.yaml";
            break;
        case MapName::AZTEC:
            map_file = "tests/client/prueba_mapa_mod.yaml";
            break;
        case MapName::NUKE:
            map_file = "tests/client/prueba_mapa_mod.yaml";
            break;
        default:
            throw std::runtime_error("Game config error: map not found");
    }

    MapLoader map_loader;
    config.map = map_loader.loadMapData(map_file);

    return config;
}
