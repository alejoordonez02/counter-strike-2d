#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <QFileInfo>
#include <stdexcept>

MapLoader::MapLoader(QObject *parent) : QObject(parent) {
    
}

MapData MapLoader::loadMapData(const QString& filePath) {
    if (!QFileInfo::exists(filePath)) {
        throw std::runtime_error("File does not exist: " + filePath.toStdString());
    }

    MapData data;
    try {
        YAML::Node config = YAML::LoadFile(filePath.toStdString());
        QFileInfo fileInfo(filePath);
        
        data.backgroundPath = QString::fromStdString(config["background"].as<std::string>());
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
        Block block;
        block.setPosition(QPoint(
            blockNode["x"].as<int>(),
            blockNode["y"].as<int>()
        ));
        block.setTexture(QString::fromStdString(blockNode["texture"].as<std::string>()));
        block.setType(QString::fromStdString(blockNode["type"].as<std::string>()));
        data.addBlock(block);
    }
}

bool MapLoader::validateMapData(const MapData& data) {
    if (data.backgroundPath.isEmpty() || !QFileInfo::exists(data.backgroundPath)) {
        return false;
    }

    if (data.plantingSpots < 1) {
        return false;
    }

    for (const auto& block : data.blocks) {
        if (block.getPosition().x() < 0 || block.getPosition().y() < 0) {
            return false;
        }
    }

    return true;
}