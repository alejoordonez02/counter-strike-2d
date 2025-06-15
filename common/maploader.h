#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <yaml-cpp/yaml.h>

struct BlockData{
    int x;
    int y;
    std::string texture;        // NOTE: se utiliza el nombre de la textura, no su path
    std::string type;
};

struct MapData{
    std::string background;
    // std::string mapName;
    // int width;
    // int height;
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
