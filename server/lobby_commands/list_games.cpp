#include "list_games.h"

#include "lobby_command.h"
#include "server/client_handler.h"

ListGamesCommand::ListGamesCommand() {}

void ListGamesCommand::execute(ClientHandler& handler) {
    handler.handle_list();
}
