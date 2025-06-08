#ifndef MOVE_H
#define MOVE_H

#include <memory>
#include <stdexcept>

#include "../../common/direction.h"
#include "../../common/network/dto.h"
#include "../../common/network/dtos/move_dto.h"
#include "../model/player.h"

#include "command.h"

/*
 * Start moving
 * */
class StartMoving: public Command {
private:
    Direction dir;

public:
    explicit StartMoving(const Direction& d): dir(d) {}

    explicit StartMoving(std::unique_ptr<DTO>&& dto_p) {
        if (MoveDTO* mov_dto = dynamic_cast<MoveDTO*>(dto_p.get())) {
            this->dir = std::move(mov_dto->dir);
        } else {
            throw std::runtime_error("DTO is not of type MoveDTO");
        }
    }

    void execute(Player& p) const override { p.start_moving(dir); }

    ~StartMoving() = default;
};

#endif
