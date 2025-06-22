#ifndef SERVER_LOBBY_COMMANDS_JOIN_GAME_H
#define SERVER_LOBBY_COMMANDS_JOIN_GAME_H

#include <string>

#include "common/team_name.h"
#include "lobby_command.h"

class ClientHandler;

class JoinGameCommand: public LobbyCommand {
    std::string game_name;
    TeamName team;

public:
    explicit JoinGameCommand(const std::string& game_name, TeamName team);
    void execute(ClientHandler& handler) override;
};

#endif
