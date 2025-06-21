#ifndef SERVER_LOBBY_COMMANDS_LIST_GAMES_H
#define SERVER_LOBBY_COMMANDS_LIST_GAMES_H

#include "lobby_command.h"

class ClientHandler;

class ListGamesCommand: public LobbyCommand {
public:
    ListGamesCommand();

    void execute(ClientHandler& handler) override;
};

#endif
