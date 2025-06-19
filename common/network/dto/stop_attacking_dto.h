#ifndef COMMON_NETWORK_DTOS_STOP_ATTACKING_DTO_H
#define COMMON_NETWORK_DTOS_STOP_ATTACKING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "dto.h"
#include "protocol.h"

class StopAttackingDTO: public DTO {
    // TODO: Solo le cambie el nombre, no tiene logica, es una copia de start
    // attacking
private:
    friend class StartAttacking;

    void deserialize() override {}

public:
    explicit StopAttackingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {
        deserialize();
    }

    StopAttackingDTO(): DTO(DTOSerial::PlayerCommands::STOP_ATTACKING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StopAttackingDTO() = default;
};

#endif
