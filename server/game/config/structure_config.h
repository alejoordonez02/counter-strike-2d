#ifndef SERVER_CONFIG_STRUCTURE_CONFIG_H
#define SERVER_CONFIG_STRUCTURE_CONFIG_H

#include "common/position.h"

enum class StructureType { COLLIDABLE, PLANTING_SPOT, TT_SPAWN, CT_SPAWN };

struct StructureConfig {
    StructureType type;
    Position pos;
    int width;
    int height;
};

#endif
