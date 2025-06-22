#ifndef COMMON_NETWORK_DTOS_AIM_DTO_H
#define COMMON_NETWORK_DTOS_AIM_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/direction.h"
#include "common/network/dto.h"
#include "common/network/protocol.h"

class AimDTO: public DTO {
    private:
    Direction dir;

    friend class Aim;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        dir = deserialize_dir_from(in);
    }

    public:
    explicit AimDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit AimDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::PlayerCommands::AIM) {
        deserialize_from(in);
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
