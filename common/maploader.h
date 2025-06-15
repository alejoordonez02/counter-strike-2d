#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <yaml-cpp/yaml.h>

struct BlockData{
    int x;
    int y;
    std::string texture;
    std::string type;
};

struct MapData{
    std::string backgroundPath;
    std::string mapName;
    int width;
    int height;
    int plantingSpots;
    std::vector<BlockData> blocks;
};

class MapLoader
{
public:
    MapLoader();
    
    MapData loadMapData(const std::string& filePath);
    
    static bool validateMapData(const MapData& data);

private:
    void parseBlocks(const YAML::Node& blocksNode, MapData& data);
};

#endif // MAPLOADER_H
