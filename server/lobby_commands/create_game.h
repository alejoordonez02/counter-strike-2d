#ifndef SERVER_LOBBY_COMMANDS_CREATE_GAME_H
#define SERVER_LOBBY_COMMANDS_CREATE_GAME_H

#include <string>

#include "common/map_name.h"
#include "server/lobby_commands/lobby_command.h"

class ClientHandler;

class CreateGameCommand: public LobbyCommand {
    std::string game_name;
    MapName map_name;

public:
    CreateGameCommand(const std::string& game_name, MapName map_name);
    void execute(ClientHandler& handler) override;
};

#endif
