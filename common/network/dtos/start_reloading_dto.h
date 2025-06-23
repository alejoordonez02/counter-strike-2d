#ifndef COMMON_NETWORK_DTOS_START_RELOADING_DTO_H
#define COMMON_NETWORK_DTOS_START_RELOADING_DTO_H

#include "common/network/dto.h"
#include "common/network/protocol.h"

class StartReloadingDTO: public DTO {
private:
    friend class StartReloading;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
    }

public:
    explicit StartReloadingDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {}

    explicit StartReloadingDTO(std::vector<uint8_t>::iterator& in):
        DTO(DTOSerial::PlayerCommands::START_RELOADING) {
        deserialize_from(in);
    }

    StartReloadingDTO(): DTO(DTOSerial::PlayerCommands::START_RELOADING) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }

    ~StartReloadingDTO() = default;
};

#endif
