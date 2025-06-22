#include "create_game.h"

#include <string>

#include "common/map_name.h"
#include "lobby_command.h"
#include "server/client_handler.h"

CreateGameCommand::CreateGameCommand(const std::string& game_name,
                                     MapName map_name, TeamName team):
    game_name(game_name), map_name(map_name), team(team) {}

void CreateGameCommand::execute(ClientHandler& handler) {
    handler.handle_create(game_name, map_name, team);
}
