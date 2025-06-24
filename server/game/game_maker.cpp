#include "game_maker.h"

#include <map>
#include <mutex>
#include <string>

#include "common/network/connection.h"
#include "config/game_config.h"
#include "factory/game_factory.h"
#include "game.h"
#include "game_maker_error.h"

void GameMaker::create(Connection&& con, const std::string& game_name,
                       MapName map, TeamName team) {
    std::unique_lock<std::mutex> lck(m);
    auto it = games.find(game_name);
    if (it != games.end()) throw GameAlreadyExists(game_name);

    GameConfig config("config/server-config.yaml", map);
    auto game = game_factory.create(config);
    /*
     * TODO: descomentar la siguiente línea cuando se implemente el manejo de
     * msjs del client lobby
     * */
    // con.send_single(LobbyCommands::SUCCESS);
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
    if (game->team_is_full(team)) throw TeamIsFull();
    /*
     * TODO: descomentar la siguiente línea cuando se implemente el manejo de
     * msjs del client lobby
     * */
    // con.send_single(LobbyCommands::SUCCESS);
    game->add_player(std::move(con), team);
}

std::vector<std::string> GameMaker::list() {
    std::unique_lock<std::mutex> lck(m);
    std::vector<std::string> game_names;
    std::transform(games.begin(), games.end(), std::back_inserter(game_names),
                   [](const auto& pair) { return pair.first; });
    return game_names;
}
