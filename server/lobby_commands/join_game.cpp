#include "join_game.h"

#include <string>

#include "lobby_command.h"
#include "server/client_handler.h"

JoinGameCommand::JoinGameCommand(const std::string& game_name, TeamName team):
    game_name(game_name), team(team) {}

void JoinGameCommand::execute(ClientHandler& handler) {
    handler.handle_join(game_name, team);
}
