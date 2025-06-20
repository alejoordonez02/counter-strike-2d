#ifndef COMMON_NETWORK_DTOS_LIST_GAMES_DTO_H
#define COMMON_NETWORK_DTOS_LIST_GAMES_DTO_H

#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class ListGamesDTO: public DTO {
private:
    void deserialize() override {}

public:
    explicit ListGamesDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    ListGamesDTO(): DTO(DTOSerial::LobbyCommands::LIST_GAMES) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
    }
};

#endif
