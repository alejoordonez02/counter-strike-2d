#ifndef COMMON_NETWORK_DTOS_PICKUP_DTO_H
#define COMMON_NETWORK_DTOS_PICKUP_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class PickupDTO: public DTO {
private:
    friend class Pickup;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit PickupDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {}

    explicit PickupDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::PICKUP) {
        deserialize_from(in);
    }

    PickupDTO(): DTO(DTOSerial::PlayerCommands::PICKUP) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~PickupDTO() = default;
};

#endif
