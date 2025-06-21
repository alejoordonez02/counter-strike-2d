#ifndef COMMON_NETWORK_DTOS_STOP_ATTACKING_DTO_H
#define COMMON_NETWORK_DTOS_STOP_ATTACKING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StopAttackingDTO: public DTO {
    // TODO: Solo le cambie el nombre, no tiene logica, es una copia de start
    // attacking
private:
    friend class StopAttacking;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StopAttackingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StopAttackingDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::STOP_ATTACKING) {
        deserialize_from(in);
    }

    StopAttackingDTO(): DTO(DTOSerial::PlayerCommands::STOP_ATTACKING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StopAttackingDTO() = default;
};

#endif
