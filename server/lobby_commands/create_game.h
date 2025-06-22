#ifndef SERVER_LOBBY_COMMANDS_CREATE_GAME_H
#define SERVER_LOBBY_COMMANDS_CREATE_GAME_H

#include <string>

#include "common/map_name.h"
#include "common/team_name.h"
#include "lobby_command.h"

class ClientHandler;

class CreateGameCommand: public LobbyCommand {
    std::string game_name;
    MapName map_name;
    TeamName team;

public:
    CreateGameCommand(const std::string& game_name, MapName map_name,
                      TeamName team);
    void execute(ClientHandler& handler) override;
};

#endif
