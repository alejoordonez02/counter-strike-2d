#include "game_maker.h"

#include <map>
#include <mutex>
#include <string>

#include "common/network/connection.h"
#include "config/game_config.h"
#include "game.h"
#include "game_maker_error.h"

void GameMaker::create(Connection&& con, const std::string& game_name,
                       MapName map, TeamName team) {
    std::unique_lock<std::mutex> lck(m);
    auto it = games.find(game_name);
    if (it != games.end()) throw GameAlreadyExists(game_name);

    GameConfig config = GameConfig::from_yaml("server-config.yaml", map);
    auto game = std::make_unique<Game>(config);
    game->add_player(std::move(con), team);
    game->start();
    games[game_name] = std::move(game);
}

void GameMaker::join(Connection&& con, const std::string& game_name,
                     TeamName team) {
    std::unique_lock<std::mutex> lck(m);
    auto it = games.find(game_name);
    if (it == games.end()) throw GameNotFound(game_name);

    auto& game = games.at(game_name);
    /*
     * acá es donde tienen que ir los checkeos, si la partida está llena, si
     * no hay lugar en el team, si ya terminó, etc; y tirar excepción, ej:
     * GameIsFull(game_name)
     * */

    game->add_player(std::move(con), team);
}

void GameMaker::list() {}
