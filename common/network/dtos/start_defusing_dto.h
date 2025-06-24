#ifndef COMMON_NETWORK_DTOS_START_DEFUSING_DTO_H
#define COMMON_NETWORK_DTOS_START_DEFUSING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StartDefusingDTO: public DTO {
private:
    friend class StartDefusing;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StartDefusingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StartDefusingDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::START_DEFUSING) {
        deserialize_from(in);
    }

    StartDefusingDTO(): DTO(DTOSerial::PlayerCommands::START_DEFUSING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StartDefusingDTO() = default;
};

#endif
