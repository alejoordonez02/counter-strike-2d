#ifndef SERVER_WORLD_PLAYER_FACTORY_H
#define SERVER_WORLD_PLAYER_FACTORY_H

#include <memory>

#include "common/team_name.h"
#include "player.h"
#include "server/config/world_config.h"
#include "server/world/map.h"

class PlayerFactory {
    std::shared_ptr<Map> map;
    WorldConfig config;

public:
    PlayerFactory(std::shared_ptr<Map> map, const WorldConfig& config);

    std::shared_ptr<Player> create(int id, TeamName team) const;
};

#endif
