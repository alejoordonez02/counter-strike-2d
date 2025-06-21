#include "world_factory.h"

#include "config/world_config.h"
#include "map_factory.h"
#include "world.h"

World WorldFactory::create(const WorldConfig& config) {
    auto map = map_factory.create(config.map);
    PlayerFactory player_factory(map, config.player);
    return World(std::move(map), config.rounds, config.round_time,
                 config.time_out, player_factory);
}
