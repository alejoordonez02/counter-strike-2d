#ifndef MOVE_H
#define MOVE_H

#include <memory>
#include <stdexcept>

#include "command.h"
#include "../model/player.h"
#include "../../common/direction.h"
#include "../../common/network/dto.h"
#include "../../common/network/dtos/move_dto.h"

/*
 * Move
 * */
class Move: public Command {
private:
    Direction dir;

public:
    explicit Move(const Direction& d): dir(d) {}

    explicit Move(std::unique_ptr<DTO>&& dto_p) {
        if (MoveDTO* mov_dto = dynamic_cast<MoveDTO*>(dto_p.get())) {
            this->dir = std::move(mov_dto->dir);
        } else {
            throw std::runtime_error("DTO is not of type MoveDTO");
        }
    }

    void execute(Player& p) const override { p.move(dir); }

    ~Move() = default;
};

#endif
