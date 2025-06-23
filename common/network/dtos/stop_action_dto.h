#ifndef COMMON_NETWORK_DTOS_STOP_ACTION_DTO_H
#define COMMON_NETWORK_DTOS_STOP_ACTION_DTO_H

#include <cstdint>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StopActionDTO: public DTO {
private:
    friend class StopAction;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StopActionDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StopActionDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::STOP_ACTION) {
        deserialize_from(in);
    }

    StopActionDTO(): DTO(DTOSerial::PlayerCommands::STOP_ACTION) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StopActionDTO() = default;
};

#endif
