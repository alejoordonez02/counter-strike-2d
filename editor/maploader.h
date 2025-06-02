#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QString>
#include <QVector>
#include <QPixmap>
#include <QPoint>
#include <yaml-cpp/yaml.h>

struct Block {
    QPoint position;
    bool isSolid;
    bool isPlantable;
};

struct MapData {
    QString backgroundPath;
    int plantingSpots;
    QVector<Block> blocks;
};

class MapLoader
{
public:
    MapLoader() = default;
    
    MapData loadMapData(const QString& filePath);
    
    static bool validateMapData(const MapData& data);

private:
    void parseBlocks(const YAML::Node& blocksNode, MapData& data);
};

#endif // MAPLOADER_H