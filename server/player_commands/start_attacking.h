#ifndef SERVER_PLAYER_COMMANDS_START_ATTACKING_H
#define SERVER_PLAYER_COMMANDS_START_ATTACKING_H

#include <memory>
#include <stdexcept>
#include <utility>

#include "common/network/dto.h"
#include "common/network/dtos/start_attacking_dto.h"
#include "server/model/player.h"
#include "server/player_commands/command.h"

/*
 * Start attacking
 * */
class StartAttacking: public Command {
public:
    StartAttacking() {}

    explicit StartAttacking(std::unique_ptr<DTO>&& dto_p) {
        StartAttackingDTO* att_dto =
                dynamic_cast<StartAttackingDTO*>(dto_p.get());
        if (not att_dto) {
            throw std::runtime_error("DTO is not of type StartAttackingDTO");
        }
    }

    void execute(Player& p) const override { p.start_attacking(); }

    ~StartAttacking() = default;
};

#endif
