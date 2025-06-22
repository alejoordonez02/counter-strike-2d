#ifndef MAPDATA_H
#define MAPDATA_H

#include <QString>
#include <QVector>
#include "block.h"
#define BACKGROUND_PREFIX "resources/backgrounds/"
#define BACKGROUND_SUFFIX ".png"

class MapDataEditor
{
public:
    QString mapName;
    QString background;
    int tile_width;
    int tile_height;
    int plantingSpots;
    QVector<Block> blocks;

    void addBlock(const Block& block) {
        blocks.append(block);
    }
    QString getBackgroundPath() const {
        return BACKGROUND_PREFIX + background + BACKGROUND_SUFFIX;
    }
};

#endif // MAPDATA_H
