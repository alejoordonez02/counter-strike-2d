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
    game_maps[game_name] = map;
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

std::vector<GameDetailsDTO> GameMaker::list() {
    std::unique_lock<std::mutex> lck(m);
    
    std::vector<GameDetailsDTO> list;
    for (const auto& [n, g]: games) {
        GameDetailsDTO dto(n,
                            g->get_tt_count(),
                            g->get_ct_count(),
                            game_maps[n],
                            g->is_joinable());
        list.push_back(std::move(dto));
    }

    return list;
}
