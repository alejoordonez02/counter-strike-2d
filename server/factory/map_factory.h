#ifndef SERVER_FACTORY_MAP_FACTORY_H
#define SERVER_FACTORY_MAP_FACTORY_H

#include "common/maploader.h"
#include "world/map.h"

class MapFactory {
public:
    MapFactory() = default;

    std::shared_ptr<Map> create(const MapData& config);
};

#endif
