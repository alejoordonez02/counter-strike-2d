#ifndef COMMON_NETWORK_DTOS_STOP_MOVING_DTO_H
#define COMMON_NETWORK_DTOS_STOP_MOVING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StopMovingDTO: public DTO {
    // TODO: Solo le cambie el nombre, no tiene logica, es una copia de start
    // moving
private:
    friend class StopMoving;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StopMovingDTO(std::vector<uint8_t>&& bytes):
            DTO(std::move(bytes)) {}

    explicit StopMovingDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::STOP_MOVING) {
        deserialize_from(in);
    }

    explicit StopMovingDTO(): DTO(DTOSerial::PlayerCommands::STOP_MOVING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StopMovingDTO() = default;
};

#endif
