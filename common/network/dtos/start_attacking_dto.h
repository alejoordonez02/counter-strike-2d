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

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StartAttackingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StartAttackingDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::START_ATTACKING) {
        deserialize_from(in);
    }

    StartAttackingDTO(): DTO(DTOSerial::PlayerCommands::START_ATTACKING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StartAttackingDTO() = default;
};

#endif
