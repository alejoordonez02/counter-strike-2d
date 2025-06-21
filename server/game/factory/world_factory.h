#ifndef SERVER_FACTORY_WORLD_FACTORY_H
#define SERVER_FACTORY_WORLD_FACTORY_H

#include "map_factory.h"
#include "server/game/config/world_config.h"
#include "server/game/world/world.h"

class WorldFactory {
private:
    MapFactory map_factory;

public:
    WorldFactory() = default;

    World create(const WorldConfig& config);
};

#endif
