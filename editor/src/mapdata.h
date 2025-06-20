#ifndef MAPDATA_H
#define MAPDATA_H

#include <QString>
#include <QVector>
#include "block.h"

class MapDataEditor
{
public:
    QString mapName;
    QString backgroundPath;
    int tile_width;
    int tile_height;
    int plantingSpots;
    QVector<Block> blocks;

    void addBlock(const Block& block) {
        blocks.append(block);
    }
};

#endif // MAPDATA_H
