#ifndef COMMON_NETWORK_DTOS_STOP_PLANTING_DTO_H
#define COMMON_NETWORK_DTOS_STOP_PLANTING_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StopPlantingDTO: public DTO {
private:
    friend class StopPlanting;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StopPlantingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StopPlantingDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::STOP_PLANTING) {
        deserialize_from(in);
    }

    StopPlantingDTO(): DTO(DTOSerial::PlayerCommands::STOP_PLANTING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StopPlantingDTO() = default;
};

#endif
