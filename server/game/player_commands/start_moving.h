#ifndef SERVER_PLAYER_COMMANDS_START_MOVING_H
#define SERVER_PLAYER_COMMANDS_START_MOVING_H

#include <memory>
#include <stdexcept>
#include <utility>

#include "common/direction.h"
#include "common/network/dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Start moving
 * */
class StartMoving: public Command {
private:
    Direction dir;

public:
    explicit StartMoving(const Direction& d): dir(d) {}

    explicit StartMoving(std::unique_ptr<DTO>&& dto_p) {
        if (StartMovingDTO* mov_dto =
                dynamic_cast<StartMovingDTO*>(dto_p.get())) {
            this->dir = std::move(mov_dto->dir);
        } else {
            throw std::runtime_error("DTO is not of type StartMovingDTO");
        }
    }

    void execute(Player& p) const override { p.start_moving(dir); }

    ~StartMoving() = default;
};

#endif
