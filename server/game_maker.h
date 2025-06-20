#ifndef GAME_MAKER_H
#define GAME_MAKER_H

#include <map>
#include <mutex>
#include <string>

#include "common/network/connection.h"
#include "game_loop.h"

class GameMaker {
private:
    std::mutex m;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GameMaker() = default;

    void create(Connection&& con, const std::string& game_name);

    void join(Connection&& con, const std::string& game_name);

    void list();
};

#endif
