#ifndef SERVER_LOBBY_COMMANDS_CMD_CONSTRUCTOR_H
#define SERVER_LOBBY_COMMANDS_CMD_CONSTRUCTOR_H

#include <memory>
#include <stdexcept>

#include "common/network/dto.h"
#include "common/network/dtos/create_game_dto.h"
#include "common/network/dtos/join_game_dto.h"
#include "server/lobby_commands/create_game.h"
#include "server/lobby_commands/join_game.h"
#include "server/lobby_commands/list_games.h"
#include "server/lobby_commands/lobby_command.h"

using namespace DTOSerial::LobbyCommands;

class LobbyCmdConstructor {
public:
    std::unique_ptr<LobbyCommand> construct(std::unique_ptr<DTO>&& dto_p) {
        uint8_t type = dto_p->get_type();
        switch (type) {
            case (uint8_t)LIST_GAMES:
                return std::make_unique<ListGamesCommand>();
            case (uint8_t)CREATE_GAME: {
                auto* dto = dynamic_cast<CreateGameDTO*>(dto_p.get());
                if (!dto) throw std::runtime_error("Bad DTO for CREATE_GAME");
                return std::make_unique<CreateGameCommand>(dto->get_game_name(),
                                                           dto->get_map());
            }
            case (uint8_t)JOIN_GAME: {
                auto* dto = dynamic_cast<JoinGameDTO*>(dto_p.get());
                if (!dto) throw std::runtime_error("Bad DTO for JOIN_GAME");
                return std::make_unique<JoinGameCommand>(dto->get_game_name());
            }
            default:
                throw std::runtime_error("Unknown lobby command type");
        }
    }
};

#endif  // SERVER_LOBBY_COMMANDS_CMD_CONSTRUCTOR_H
