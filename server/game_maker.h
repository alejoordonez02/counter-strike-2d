#ifndef GAME_MAKER_H
#define GAME_MAKER_H

#include <map>
#include <mutex>
#include <string>

#include "common/network/connection.h"
#include "game_loop.h"
#include "game_maker_error.h"
#include "game_setup.h"

class GameMaker {
private:
    std::mutex m;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GameMaker() = default;

    void create(Connection&& con, const std::string& game_name) {
        std::unique_lock<std::mutex> lck(m);
        auto it = games.find(game_name);
        if (it != games.end()) throw GameAlreadyExists(game_name);

        auto player = GameSetup::create_player();
        auto player_handler =
            std::make_unique<PlayerHandler>(std::move(con), player);
        auto game = GameSetup::create_game();
        game->start();
        player_handler->start();
        game->add_player(std::move(player_handler));
        games[game_name] = std::move(game);
    }

    void join(Connection&& con, const std::string& game_name) {
        std::unique_lock<std::mutex> lck(m);
        auto it = games.find(game_name);
        if (it == games.end()) throw GameNotFound(game_name);

        auto& game = games.at(game_name);
        // if (game->is_full(/* team */)) throw GameIsFull(game_name);

        auto player = GameSetup::create_player();
        auto player_handler =
            std::make_unique<PlayerHandler>(std::move(con), player);
        game->add_player(std::move(player_handler));
    }

    void list() {}
};

#endif
