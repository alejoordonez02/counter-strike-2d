#ifndef COMMON_NETWORK_DTOS_DROP_BOMB_DTO_H
#define COMMON_NETWORK_DTOS_DROP_BOMB_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class DropBombDTO: public DTO {
private:
    friend class DropBomb;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit DropBombDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {}

    explicit DropBombDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::DROP_BOMB) {
        deserialize_from(in);
    }

    DropBombDTO(): DTO(DTOSerial::PlayerCommands::DROP_BOMB) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~DropBombDTO() = default;
};

#endif
