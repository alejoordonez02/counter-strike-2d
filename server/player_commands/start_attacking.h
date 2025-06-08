#ifndef ATTACK_H
#define ATTACK_H

#include <memory>
#include <stdexcept>

#include "../../common/network/dto.h"
#include "../../common/network/dtos/attack_dto.h"
#include "../../common/position.h"
#include "../model/player.h"

#include "command.h"

/*
 * Attack
 * */
class StartAttacking: public Command {
private:
    Position pos;

public:
    explicit StartAttacking(const Position& p): pos(p) {}

    explicit StartAttacking(std::unique_ptr<DTO>&& dto_p) {
        if (AttackDTO* att_dto = dynamic_cast<AttackDTO*>(dto_p.get())) {
            this->pos = std::move(att_dto->pos);
        } else {
            throw std::runtime_error("DTO is not of type AttackDTO");
        }
    }

    void execute(Player& p) const override { p.start_attacking(); }

    ~StartAttacking() = default;
};

#endif
