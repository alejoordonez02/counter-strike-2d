#ifndef COMMON_NETWORK_DTOS_START_ATTACKING_DTO_H
#define COMMON_NETWORK_DTOS_START_ATTACKING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StartAttackingDTO: public DTO {
    private:
    friend class StartAttacking;

    void deserialize() override {}

    public:
    explicit StartAttackingDTO(std::vector<uint8_t>&& bytes):
            DTO(std::move(bytes)) {
        deserialize();
    }

    StartAttackingDTO(): DTO(DTOSerial::PlayerCommands::ATTACK) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StartAttackingDTO() = default;
};

#endif
