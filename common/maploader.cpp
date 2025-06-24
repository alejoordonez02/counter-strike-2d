#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <iostream>


MapLoader::MapLoader() {
}

MapData MapLoader::loadMapData(MapName map_name) {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    std::string yaml_path;
    switch (map_name) {
        #define X(name, lowercase) \
                case MapName::name: \
                    yaml_path = "config/maps/" lowercase ".yaml"; \
                    break;
            MAP_LIST
        #undef X
        default:
            throw std::runtime_error("MapLoader error: map not found");
    }
    
    return loadMapYaml(yaml_path);
}

MapData MapLoader::loadMapYaml(const std::string& filePath) {
    MapData data;
    try {
        YAML::Node config = YAML::LoadFile(filePath);
        data.mapName = config["map_name"].as<std::string>();
        data.background = config["background"].as<std::string>();
        data.width = config["tile_width"].as<int>();
        data.height = config["tile_height"].as<int>();
        data.plantingSpots = config["planting_spots"].as<int>();
        if (config["blocks"]) {
            parseBlocks(config["blocks"], data);
        }

        if (!validateMapData(data)) {
            throw std::runtime_error("Map data validation failed");
        }

    } catch (const YAML::Exception& e) {
        throw std::runtime_error("YAML Error: " + std::string(e.what()));
    }

    return data;
}

void MapLoader::parseBlocks(const YAML::Node& blocksNode, MapData& data) {
    for (const auto& blockNode : blocksNode) {
        BlockData block;
        block.x = blockNode["x"].as<int>();
        block.y = blockNode["y"].as<int>();
        block.texture = blockNode["texture"].as<std::string>();
        block.type = blockNode["type"].as<std::string>();
        data.blocks.push_back(block);
    }
}

bool MapLoader::validateMapData(const MapData& data) {
    if (data.background.empty()){ 
        return false;
    }

    if (data.plantingSpots < 1) {
        return false;
    }

    for (const auto& block : data.blocks) {
        if (block.x < 0 || block.y < 0) {
            return false;
        }
    }

    return true;
}