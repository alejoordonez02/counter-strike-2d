#ifndef SERVER_WORLD_PLAYER_FACTORY_H
#define SERVER_WORLD_PLAYER_FACTORY_H

#include <memory>

#include "common/team_name.h"
#include "server/game/config/player_config.h"
#include "server/game/world/map.h"
#include "server/game/world/player.h"
#include "weapon_factory.h"

class PlayerFactory {
    std::shared_ptr<Map> map;
    std::shared_ptr<WeaponFactory> weapon_factory;
    PlayerConfig config;

public:
    PlayerFactory(std::shared_ptr<Map> map, const PlayerConfig& config,
                  std::shared_ptr<WeaponFactory> weapon_factory);

    std::shared_ptr<Player> create(int id, TeamName team) const;
};

#endif
