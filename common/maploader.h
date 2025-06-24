#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <yaml-cpp/yaml.h>

#include "common/map_name.h"

/*
 * TODO: refactorizar:
 * - usar Position, está en common
 * - preferir siempre enums antes que strings, por lo menos para el tipo
 *   de bloque, hay una implementación del mapeo de strings en map_factory.cpp
 * Ej:
 * struct StructureConfig {
 *     StructureType type;
 *     Position pos;
 *     int width;
 *     int height;
 * };
 * */
struct BlockData {
    int x;
    int y;
    std::string
        texture;  // NOTE: se utiliza el nombre de la textura, no su path
    std::string type;
};

struct MapData {
    std::string background;
    std::string mapName;
    int width;
    int height;
    int plantingSpots;
    std::vector<BlockData> blocks;
};

class MapLoader {
public:
    MapLoader();

    MapData loadMapData(MapName map_name);
    MapData loadMapYaml(const std::string& filePath);

    static bool validateMapData(const MapData& data);

private:
    void parseBlocks(const YAML::Node& blocksNode, MapData& data);
};

#endif  // MAPLOADER_H
