#ifndef SERVER_FACTORY_MAP_FACTORY_H
#define SERVER_FACTORY_MAP_FACTORY_H

#include "common/maploader.h"
#include "server/game/world/map.h"
#include "weapon_factory.h"

class MapFactory {
public:
    MapFactory() = default;

    std::shared_ptr<Map> create(const MapData& config,
                                std::shared_ptr<WeaponFactory> weapon_factory);
};

#endif
