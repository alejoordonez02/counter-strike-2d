#ifndef SERVER_PLAYER_COMMANDS_AIM_H
#define SERVER_PLAYER_COMMANDS_AIM_H

#include <memory>
#include <stdexcept>
#include <utility>

#include "common/direction.h"
#include "common/network/dtos/aim_dto.h"
#include "server/model/player.h"
#include "server/player_commands/command.h"

/*
 * Aim
 * */
class Aim: public Command {
private:
    Direction dir;

public:
    explicit Aim(const Direction& d): dir(d) {}

    explicit Aim(std::unique_ptr<DTO>&& dto_p) {
        if (AimDTO* aim_dto = dynamic_cast<AimDTO*>(dto_p.get())) {
            this->dir = std::move(aim_dto->dir);
        } else {
            throw std::runtime_error("DTO is not of type AimDTO");
        }
    }

    void execute(Player& p) const override { p.aim(dir); }

    ~Aim() = default;
};

#endif
