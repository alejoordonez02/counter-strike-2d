#include "map_factory.h"

#include "common/maploader.h"
#include "world/map.h"

std::shared_ptr<Map> MapFactory::create(const MapData& config) {
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::vector<Structure> bomb_site;
    std::vector<Position> tt_spawn;
    std::vector<Position> ct_spawn;
    for (auto& block : config.blocks) {
        if (block.type == "Solid")
            collidables.push_back(
                std::make_shared<Structure>(Position(block.x, block.y), 32));
        else if (block.type == "Plantable")
            bomb_site.push_back(Structure(Position(block.x, block.y), 32));
        else if (block.type == "TSpawn")
            tt_spawn.push_back(Position(block.x, block.y));
        else if (block.type == "CtSpawn")
            ct_spawn.push_back(Position(block.x, block.y));
    }

    return std::make_shared<Map>(collidables, bomb_site, tt_spawn, ct_spawn);
}
