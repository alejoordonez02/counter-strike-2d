#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <stdexcept>
#include <fstream>


MapLoader::MapLoader() {
}

MapData MapLoader::loadMapData(const std::string& filePath) {
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error("File does not exist: " + filePath);
    }

    MapData data;
    try {
        YAML::Node config = YAML::LoadFile(filePath);

        data.backgroundPath = config["background"].as<std::string>();
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
    if (data.backgroundPath.empty() || !std::filesystem::exists(data.backgroundPath)) {
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