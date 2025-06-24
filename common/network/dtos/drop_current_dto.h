#ifndef COMMON_NETWORK_DTOS_DROP_CURRENT_DTO_H
#define COMMON_NETWORK_DTOS_DROP_CURRENT_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class DropCurrentDTO: public DTO {
private:
    friend class DropCurrent;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit DropCurrentDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit DropCurrentDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::DROP_CURRENT) {
        deserialize_from(in);
    }

    DropCurrentDTO(): DTO(DTOSerial::PlayerCommands::DROP_CURRENT) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~DropCurrentDTO() = default;
};

#endif
