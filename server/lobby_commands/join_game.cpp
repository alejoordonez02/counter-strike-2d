#include "server/lobby_commands/join_game.h"

#include <string>

#include "server/client_handler.h"
#include "server/lobby_commands/lobby_command.h"

JoinGameCommand::JoinGameCommand(const std::string& game_name, TeamName team):
    game_name(game_name), team(team) {}

void JoinGameCommand::execute(ClientHandler& handler) {
    handler.handle_join(game_name, team);
}
