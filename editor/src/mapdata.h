#ifndef MAPDATA_H
#define MAPDATA_H

#include <QString>
#include <QVector>
#include "block.h"

class MapData
{
public:
    QString backgroundPath;
    int plantingSpots;
    QVector<Block> blocks;

    void addBlock(const Block& block) {
        blocks.append(block);
    }
};

#endif // MAPDATA_H
