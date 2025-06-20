#ifndef SERVER_WORLD_PLAYER_FACTORY_H
#define SERVER_WORLD_PLAYER_FACTORY_H

#include <functional>
#include <memory>

#include "player.h"

using PlayerFactory = std::function<std::shared_ptr<Player>(int id)>;

#endif
