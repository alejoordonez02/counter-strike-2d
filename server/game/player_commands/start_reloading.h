#ifndef SERVER_PLAYER_COMMANDS_START_RELOADING_H
#define SERVER_PLAYER_COMMANDS_START_RELOADING_H

#include <memory>
#include <stdexcept>
#include <utility>

#include "common/network/dto.h"
#include "player_command.h"
#include "server/game/world/player.h"
#include "start_reloading_dto.h"

/*
 * Start reloading
 * */
class StartReloading: public Command {
public:
    StartReloading() {}

    explicit StartReloading(std::unique_ptr<DTO>&& dto_p) {
        StartReloadingDTO* att_dto =
            dynamic_cast<StartReloadingDTO*>(dto_p.get());
        if (not att_dto) {
            throw std::runtime_error("DTO is not of type StartReloadingDTO");
        }
    }

    void execute(Player& p) const override { p.start_reloading(); }

    ~StartReloading() = default;
};

#endif
