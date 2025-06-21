#include "game_factory.h"

#include "server/game/config/game_config.h"
#include "server/game/game.h"
#include "world_factory.h"

std::unique_ptr<Game> GameFactory::create(const GameConfig& config) {
    World world = world_factory.create(config.world);
    return std::make_unique<Game>(std::move(world), config.loop.tick_rate,
                                  config.loop.commands_per_tick);
}
