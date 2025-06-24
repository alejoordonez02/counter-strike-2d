#ifndef SERVER_LOBBY_COMMANDS_COMMAND_H
#define SERVER_LOBBY_COMMANDS_COMMAND_H

class ClientHandler;

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
