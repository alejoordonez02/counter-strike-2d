#ifndef SERVER_FACTORY_GAME_FACTORY_H
#define SERVER_FACTORY_GAME_FACTORY_H

#include "config/game_config.h"
#include "game.h"
#include "world_factory.h"

class GameFactory {
private:
    WorldFactory world_factory;

public:
    GameFactory() = default;

    std::unique_ptr<Game> create(const GameConfig& config);
};

#endif
