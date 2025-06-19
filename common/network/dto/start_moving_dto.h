#ifndef COMMON_NETWORK_DTOS_START_MOVING_DTO_H
#define COMMON_NETWORK_DTOS_START_MOVING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "direction.h"
#include "dto.h"
#include "protocol.h"

class StartMovingDTO: public DTO {
private:
    Direction dir;

    friend class StartMoving;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        dir = deserialize_dir(i);
    }

public:
    explicit StartMovingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {
        deserialize();
    }

    explicit StartMovingDTO(const Direction& d):
        DTO(DTOSerial::PlayerCommands::START_MOVING), dir(d) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_dir_into(out, dir);
    }

    Direction get_direction() { return dir; }

    ~StartMovingDTO() = default;
};

#endif
