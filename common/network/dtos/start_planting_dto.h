#ifndef COMMON_NETWORK_DTOS_START_PLANTING_DTO_H
#define COMMON_NETWORK_DTOS_START_PLANTING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StartPlantingDTO: public DTO {
private:
    friend class StartPlanting;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StartPlantingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StartPlantingDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::START_PLANTING) {
        deserialize_from(in);
    }

    StartPlantingDTO(): DTO(DTOSerial::PlayerCommands::START_PLANTING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StartPlantingDTO() = default;
};

#endif
