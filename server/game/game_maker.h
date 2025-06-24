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

class GameMaker {
private:
    std::mutex m;
    std::map<std::string, std::unique_ptr<Game>> games;

    GameFactory game_factory;

public:
    GameMaker() = default;

    void create(Connection&& con, const std::string& game_name, MapName map,
                TeamName team);

    void join(Connection&& con, const std::string& game_name, TeamName team);

    std::vector<std::string> list();
};

#endif
