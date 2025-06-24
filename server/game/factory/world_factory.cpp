#include "world_factory.h"

#include "map_factory.h"
#include "server/game/config/world_config.h"
#include "server/game/world/world.h"

World WorldFactory::create(const WorldConfig& config) {
    auto map = map_factory.create(config.map);
    auto weapon_factory = std::make_shared<WeaponFactory>(config.weapons);
    PlayerFactory player_factory(map, config.player, weapon_factory);
    return World(std::move(map), config.rounds, config.round_time,
                 config.time_out, player_factory, weapon_factory);
}
