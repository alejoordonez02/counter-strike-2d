#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <QFileInfo>
#include <stdexcept>

MapData MapLoader::loadMapData(const QString& filePath) {
    // Verify file exists
    if (!QFileInfo::exists(filePath)) {
        throw std::runtime_error("File does not exist: " + filePath.toStdString());
    }

    MapData data;
    
    try {
        YAML::Node config = YAML::LoadFile(filePath.toStdString());

        // Load basic data
        data.backgroundPath = QString::fromStdString(config["background"].as<std::string>());
        data.plantingSpots = config["planting_spots"].as<int>();

        // Load blocks using the parseBlocks method
        if (config["blocks"]) {
            parseBlocks(config["blocks"], data);
        }

        // Validate the loaded data
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
        Block block;
        block.position = QPoint(
            blockNode["x"].as<int>(),
            blockNode["y"].as<int>()
        );
        block.isSolid = blockNode["solid"].as<bool>();
        block.isPlantable = blockNode["plantable"].as<bool>();
        data.blocks.append(block);
    }
}

bool MapLoader::validateMapData(const MapData& data) {
    // Validate background path
    if (data.backgroundPath.isEmpty() || !QFileInfo::exists(data.backgroundPath)) {
        return false;
    }

    // Validate planting spots
    if (data.plantingSpots < 1) {
        return false;
    }

    // Validate block positions
    for (const auto& block : data.blocks) {
        if (block.position.x() < 0 || block.position.y() < 0) {
            return false;
        }
    }

    return true;
}