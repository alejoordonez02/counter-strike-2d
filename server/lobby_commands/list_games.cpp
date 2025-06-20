#include "server/lobby_commands/list_games.h"

#include "server/client_handler.h"
#include "server/lobby_commands/lobby_command.h"

ListGamesCommand::ListGamesCommand() {}

void ListGamesCommand::execute(ClientHandler& handler) {
    handler.handle_list();
}
