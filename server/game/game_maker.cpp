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
    con.send_single(LobbyCommands::SUCCESS);
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
    con.send_single(LobbyCommands::SUCCESS);
    game->add_player(std::move(con), team);
}

std::vector<std::string> GameMaker::list() {
    std::unique_lock<std::mutex> lck(m);
    
    std::vector<std::unique_ptr<GameDetailsDTO>> list;
    for (const auto& [n, g]: games) {
        list.push_back(g->get_details_dto());
    }

    return list;
}
