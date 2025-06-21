#ifndef SERVER_CONFIG_MAP_CONFIG_H
#define SERVER_CONFIG_MAP_CONFIG_H

#include <vector>

#include "structure_config.h"

struct MapConfig {
    std::vector<StructureConfig> structures;
};

#endif
