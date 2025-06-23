#ifndef SERVER_PLAYER_COMMANDS_START_PLANTING_H
#define SERVER_PLAYER_COMMANDS_START_PLANTING_H

#include <memory>
#include <stdexcept>
#include <utility>

#include "common/network/dto.h"
#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_planting_dto.h"
#include "player_command.h"
#include "server/game/world/player.h"

/*
 * Start attacking
 * */
class StartPlanting: public Command {
public:
    StartPlanting() {}

    explicit StartPlanting(std::unique_ptr<DTO>&& dto_p) {
        StartPlantingDTO* att_dto =
            dynamic_cast<StartPlantingDTO*>(dto_p.get());
        if (not att_dto) {
            throw std::runtime_error("DTO is not of type StartPlantingDTO");
        }
    }

    void execute(Player& p) const override { p.plant_bomb(); }

    ~StartPlanting() = default;
};

#endif
