#ifndef START_ATTACKING_DTO_H
#define START_ATTACKING_DTO_H

#include <cstdint>
#include <vector>

#include "../../position.h"
#include "../dto.h"
#include "../protocol.h"

class StartAttackingDTO: public DTO {
private:
    friend class StartAttacking;

    void deserialize() override {}

public:
    explicit StartAttackingDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    explicit StartAttackingDTO(): DTO(DTOSerial::PlayerCommands::ATTACK) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StartAttackingDTO() = default;
};

#endif
