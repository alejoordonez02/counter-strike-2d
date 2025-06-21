#ifndef SERVER_WORLD_PLAYER_FACTORY_H
#define SERVER_WORLD_PLAYER_FACTORY_H

#include <memory>

#include "common/team_name.h"
#include "config/player_config.h"
#include "server/game/world/map.h"
#include "server/game/world/player.h"

class PlayerFactory {
    std::shared_ptr<Map> map;
    PlayerConfig config;

public:
    PlayerFactory(std::shared_ptr<Map> map, const PlayerConfig& config);

    std::shared_ptr<Player> create(int id, TeamName team) const;
};

#endif
