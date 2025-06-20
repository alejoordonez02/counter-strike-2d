#ifndef SERVER_LOBBY_COMMANDS_JOIN_GAME_H
#define SERVER_LOBBY_COMMANDS_JOIN_GAME_H

#include <string>

#include "server/lobby_commands/lobby_command.h"

class ClientHandler;

class JoinGameCommand: public LobbyCommand {
    std::string game_name;

public:
    explicit JoinGameCommand(const std::string& game_name);
    void execute(ClientHandler& handler) override;
};

#endif
