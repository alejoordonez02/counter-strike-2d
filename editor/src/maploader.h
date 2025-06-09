#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <QString>
#include <QVector>
#include <QPoint>
#include <QPixmap>
#include <QMap>
#include <yaml-cpp/yaml.h>
#include "block.h"
#include "mapdata.h"

class MapLoader : public QObject
{
    Q_OBJECT

public:
    explicit MapLoader(QObject *parent = nullptr);
    
    MapData loadMapData(const QString& filePath);
    
    static bool validateMapData(const MapData& data);

signals:
    void textureLoaded(const QString& id, const QPixmap& texture);

private:
    void parseBlocks(const YAML::Node& blocksNode, MapData& data);
    void loadTextureResources(MapData& data);
};

#endif // MAPLOADER_H
