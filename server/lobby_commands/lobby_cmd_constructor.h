#ifndef SERVER_LOBBY_COMMANDS_CMD_CONSTRUCTOR_H
#define SERVER_LOBBY_COMMANDS_CMD_CONSTRUCTOR_H

#include <memory>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "lobby_command.h"

using namespace DTOSerial::LobbyCommands;

class LobbyCmdConstructor {
public:
    std::unique_ptr<LobbyCommand> construct(std::unique_ptr<DTO>&& dto_p);
};

#endif  // SERVER_LOBBY_COMMANDS_CMD_CONSTRUCTOR_H
