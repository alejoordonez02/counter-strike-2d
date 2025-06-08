#ifndef ATTACK_H
#define ATTACK_H

#include <memory>
#include <stdexcept>

#include "command.h"
#include "../model/player.h"
#include "../../common/position.h"
#include "../../common/network/dto.h"
#include "../../common/network/dtos/attack_dto.h"

/*
 * Attack
 * */
class Attack: public Command {
private:
    Position pos;

public:
    explicit Attack(const Position& p): pos(p) {}

    explicit Attack(std::unique_ptr<DTO>&& dto_p) {
        if (AttackDTO* att_dto = dynamic_cast<AttackDTO*>(dto_p.get())) {
            this->pos = std::move(att_dto->pos);
        } else {
            throw std::runtime_error("DTO is not of type AttackDTO");
        }
    }

    void execute(Player& p) const override { p.attack(pos); }
    
    ~Attack() = default;
};

#endif
