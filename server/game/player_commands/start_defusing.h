#ifndef SERVER_PLAYER_COMMANDS_START_DEFUSING_H
#define SERVER_PLAYER_COMMANDS_START_DEFUSING_H

#include <memory>
#include <stdexcept>

#include "common/network/dto.h"
#include "common/network/dtos/start_defusing_dto.h"
#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Start defusing
 * */
class StartDefusing: public Command {
public:
    StartDefusing() {}

    explicit StartDefusing(std::unique_ptr<DTO>&& dto_p) {
        StartDefusingDTO* att_dto =
            dynamic_cast<StartDefusingDTO*>(dto_p.get());
        if (not att_dto) {
            throw std::runtime_error("DTO is not of type StartDefusingDTO");
        }
    }

    void execute(Player& p) const override { p.start_defusing(); }

    ~StartDefusing() = default;
};

#endif
