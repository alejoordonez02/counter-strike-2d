#ifndef COMMON_NETWORK_DTOS_STOP_MOVING_DTO_H
#define COMMON_NETWORK_DTOS_STOP_MOVING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/direction.h"
#include "common/network/dto.h"
#include "common/network/protocol.h"

class StopMovingDTO: public DTO {
    // TODO: Solo le cambie el nombre, no tiene logica, es una copia de start moving
private:
    Direction dir;

    friend class StartMoving;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        dir = deserialize_dir(i);
    }

public:
    explicit StopMovingDTO(std::vector<uint8_t>&& bytes):
            DTO(std::move(bytes)) {
        deserialize();
    }

    explicit StopMovingDTO(const Direction& d):
            DTO(DTOSerial::PlayerCommands::MOVE), dir(d) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_dir_into(out, dir);
    }

    Direction get_direction() { return dir; }

    ~StopMovingDTO() = default;
};

#endif
