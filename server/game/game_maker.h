#ifndef GAME_MAKER_H
#define GAME_MAKER_H

#include <map>
#include <mutex>
#include <string>

#include "common/map_name.h"
#include "common/network/connection.h"
#include "common/team_name.h"
#include "factory/game_factory.h"
#include "game.h"
#include "common/network/dtos/game_details_dto.h"

class GameMaker {
private:
    std::mutex m;
    std::map<std::string, std::unique_ptr<Game>> games;
    std::map<std::string, MapName> game_maps;

    GameFactory game_factory;

public:
    GameMaker() = default;

    void create(Connection&& con, const std::string& game_name, MapName map,
                TeamName team);

    void join(Connection&& con, const std::string& game_name, TeamName team);

    std::vector<GameDetailsDTO> list();
};

#endif
