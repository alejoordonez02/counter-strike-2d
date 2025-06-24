#include "game_config.h"

#include <iostream>
#include <stdexcept>

#include "common/maploader.h"

/*
 * Loop and world configs
 * */
void GameConfig::load_world_config(YAML::Node config, MapName map) {
    std::cout << "loading world config\n";
    try {
        world.rounds = config["rounds"].as<int>();
        world.round_time = config["round_time"].as<float>();
        world.time_out = config["time_out"].as<float>();
        world.map = load_map_config(map);
        world.player = load_player_config(config["player"]);
        world.weapons = load_weapon_configs(config["weapons"]);
    } catch (const std::exception& e) {
        std::cerr << "Error loading world config: " << e.what() << std::endl;
        throw std::runtime_error(
            "Game config error: invalid world configuration");
    }
}

void GameConfig::load_loop_config(YAML::Node config) {
    std::cout << "loading loop config\n";
    try {
        loop.tick_rate = config["tick_rate"].as<int>();
        loop.commands_per_tick = config["commands_per_tick"].as<int>();
    } catch (...) {
        std::cerr << "Error loading loop config" << std::endl;
        throw std::runtime_error(
            "Game config error: invalid loop configuration");
    }
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
    try {
        player.max_velocity = config["max_velocity"].as<float>();
        player.acceleration = config["acceleration"].as<float>();
        player.radius = config["radius"].as<float>();
        player.starting_money = config["starting_money"].as<int>();
        player.max_health = config["max_health"].as<int>();
    } catch (...) {
        std::cerr << "Error loading player config" << std::endl;
        throw std::runtime_error(
            "Game config error: invalid player configuration");
    }
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

    std::map<std::string, WeaponType> weapon_type_map = {
        {"Primary", WeaponType::PRIMARY},
        {"Secondary", WeaponType::SECONDARY},
        {"Knife", WeaponType::KNIFE}};

    std::cout << "loading weapon config\n";
    std::map<WeaponName, WeaponConfig> weapons;
    for (auto c : configs) {
        try {
            auto config = c.second;
            WeaponName name = weapon_name_map.at(c.first.as<std::string>());
            WeaponConfig weapon;
            weapon.type = weapon_type_map.at(config["type"].as<std::string>());
            weapon.damage = config["damage"].as<float>();
            weapon.accuracy = config["accuracy"].as<float>();
            weapon.range = config["range"].as<float>();
            weapon.bullet_size = config["bullet_size"].as<float>();
            weapon.fire_rate = config["fire_rate"].as<float>();
            weapon.reload_time = config["reload_time"].as<float>();
            weapon.ammo_capacity = config["ammo_capacity"].as<int>();
            weapon.starting_ammo = config["starting_ammo"].as<int>();
            weapon.cost = config["cost"].as<int>();
            weapon.ammo_cost = config["ammo_cost"].as<int>();
            weapons[name] = weapon;
        } catch (const std::exception& e) {
            std::cerr << "Error loading weapon config for "
                      << c.first.as<std::string>() << ": " << e.what()
                      << std::endl;
            throw std::runtime_error(
                "Game config error: invalid weapon configuration");
        }
    }
    return weapons;
}
