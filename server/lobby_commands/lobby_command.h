#ifndef SERVER_LOBBY_COMMANDS_COMMAND_H
#define SERVER_LOBBY_COMMANDS_COMMAND_H

#include <cstdint>

class ClientHandler;

enum class LobbyCommandType : uint8_t {
    CHANGE_USERNAME,
    LIST_GAMES,
    CREATE_GAME,
    JOIN_GAME,
    EXIT_SERVER
};

class LobbyCommand {
protected:
    LobbyCommand() = default;

public:
    virtual void execute(ClientHandler& handler) = 0;
    virtual ~LobbyCommand() = default;
    LobbyCommand(const LobbyCommand&) = delete;
    LobbyCommand& operator=(const LobbyCommand&) = delete;
    LobbyCommand(LobbyCommand&&) = default;
    LobbyCommand& operator=(LobbyCommand&&) = default;
};

#endif
