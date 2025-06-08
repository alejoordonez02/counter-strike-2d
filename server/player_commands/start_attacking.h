#ifndef START_ATTACKING_H
#define START_ATTACKING_H

#include <memory>
#include <stdexcept>

#include "../../common/network/dto.h"
#include "../../common/network/dtos/start_attacking_dto.h"
#include "../../common/position.h"
#include "../model/player.h"

#include "command.h"

/*
 * Start attacking
 * */
class StartAttacking: public Command {
public:
    explicit StartAttacking() {}

    explicit StartAttacking(std::unique_ptr<DTO>&& dto_p) {
        if (StartAttackingDTO* att_dto = dynamic_cast<StartAttackingDTO*>(dto_p.get())) {
        } else {
            throw std::runtime_error("DTO is not of type StartAttackingDTO");
        }
    }

    void execute(Player& p) const override { p.start_attacking(); }

    ~StartAttacking() = default;
};

#endif
