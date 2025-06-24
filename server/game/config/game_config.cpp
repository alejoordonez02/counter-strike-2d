#include "game_config.h"

#include <iostream>
#include <stdexcept>

#include "common/maploader.h"

/*
 * Loop and world configs
 * */
void GameConfig::load_world_config(YAML::Node config, MapName map) {
    std::cout << "loading world config\n";
    world.rounds = config["rounds"].as<int>();
    world.round_time = config["round_time"].as<float>();
    world.time_out = config["time_out"].as<float>();
    world.map = load_map_config(map);
    world.player = load_player_config(config["player"]);
    world.weapons = load_weapon_configs(config["weapons"]);
}

void GameConfig::load_loop_config(YAML::Node config) {
    std::cout << "loading loop config\n";
    loop.tick_rate = config["tick_rate"].as<int>();
    loop.commands_per_tick = config["commands_per_tick"].as<int>();
}

GameConfig::GameConfig(const std::string& path, MapName map) {
    std::cout << "loading game config\n";
    YAML::Node yaml = YAML::LoadFile(path);
    load_loop_config(yaml["loop"]);
    load_world_config(yaml["world"], map);
}

/*
 * Config helpers
 * */
/*
 * No están los mapas definidos todavía así que uso el mismo para todos.
 * TODO: ésto debería estar en common! la traducción del enum es la misma
 * para el server que para el cliente (y que se llame MapConfig con un
 * vector de structs StructureConfig porfa jsjajaj)
 * */
MapData GameConfig::load_map_config(MapName map_name) {
    std::cout << "loading map config\n";
    std::string map_yaml;
    switch (map_name) {
        case MapName::DUST:
            map_yaml = "tests/client/prueba_mapa_mod.yaml";
            break;
        case MapName::AZTEC:
            map_yaml = "tests/client/prueba_mapa_mod.yaml";
            break;
        case MapName::NUKE:
            map_yaml = "tests/client/prueba_mapa_mod.yaml";
            break;
        default:
            throw std::runtime_error("Game config error: map not found");
    }
    MapLoader map_loader;
    return map_loader.loadMapData(map_yaml);
}

PlayerConfig GameConfig::load_player_config(YAML::Node config) {
    std::cout << "loading player config\n";
    PlayerConfig player;
    player.max_velocity = config["max_velocity"].as<float>();
    player.acceleration = config["acceleration"].as<float>();
    player.radius = config["radius"].as<float>();
    player.starting_money = config["starting_money"].as<int>();
    player.max_health = config["max_health"].as<int>();
    return player;
}

std::map<WeaponName, WeaponConfig> GameConfig::load_weapon_configs(
    YAML::Node configs) {
    /*
     * TODO: éste map seguramente tenga que estar en common, en common/weapons.h
     * */
    std::map<std::string, WeaponName> weapon_name_map = {
        {"Glock", WeaponName::GLOCK},
        {"Ak47", WeaponName::AK47},
        {"M3", WeaponName::M3},
        {"Awp", WeaponName::AWP},
        {"Knife", WeaponName::KNIFE}};

    std::cout << "loading weapon config\n";
    std::map<WeaponName, WeaponConfig> weapons;
    for (auto c : configs) {
        std::string name = c.first.as<std::string>();
        auto config = c.second;
        WeaponConfig weapon;
        weapon.damage = config["damage"].as<int>();
        weapon.ammo = config["ammo"].as<int>();
        weapon.accuracy = config["accuracy"].as<float>();
        weapon.range = config["range"].as<float>();
        weapon.fire_rate = config["fire_rate"].as<float>();
        weapon.cost = config["cost"].as<int>();
        weapon.ammo_cost = config["ammo_cost"].as<int>();
        weapons[weapon_name_map.at(name)] = weapon;
    }
    return weapons;
}
