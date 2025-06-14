#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <yaml-cpp/yaml.h>
// #include "mapdata.h"

struct BlockData{
    int x;
    int y;
    std::string texture;
    std::string type;
};

struct MapOnlyData{
    std::string backgroundPath;
    int plantingSpots;
    std::vector<BlockData> blocks;
};

class MapLoader
{
public:
    MapLoader();
    
    MapOnlyData loadMapData(const std::string& filePath);
    
    static bool validateMapData(const MapOnlyData& data);

private:
    void parseBlocks(const YAML::Node& blocksNode, MapOnlyData& data);
};

#endif // MAPLOADER_H
