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

    void deserialize() override {}

public:
    explicit StopMovingDTO(std::vector<uint8_t>&& bytes):
            DTO(std::move(bytes)) {
        deserialize();
    }

    explicit StopMovingDTO(): DTO(DTOSerial::PlayerCommands::STOP_MOVING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StopMovingDTO() = default;
};

#endif
