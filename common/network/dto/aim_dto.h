#ifndef COMMON_NETWORK_DTOS_AIM_DTO_H
#define COMMON_NETWORK_DTOS_AIM_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "direction.h"
#include "dto.h"
#include "protocol.h"

class AimDTO: public DTO {
private:
    Direction dir;

    friend class Aim;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        dir = deserialize_dir(i);
    }

public:
    explicit AimDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    explicit AimDTO(const Direction& d):
        DTO(DTOSerial::PlayerCommands::AIM), dir(d) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_dir_into(out, dir);
    }

    ~AimDTO() = default;
};

#endif
