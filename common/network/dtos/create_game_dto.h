#ifndef COMMON_NETWORK_DTOS_CREATE_GAME_DTO_H
#define COMMON_NETWORK_DTOS_CREATE_GAME_DTO_H

#include <string>
#include <vector>

#include "common/map_name.h"
#include "common/network/dto.h"
#include "common/network/protocol.h"

class CreateGameDTO: public DTO {
private:
    std::string game_name;
    MapName map;

    void deserialize() override {
        int i = 1;
        uint8_t len = payload[i++];
        game_name.assign(payload.begin() + i, payload.begin() + i + len);
        i += len;
        map = static_cast<MapName>(payload[i++]);
    }

public:
    explicit CreateGameDTO(std::vector<uint8_t>&& bytes):
        DTO(std::move(bytes)) {
        deserialize();
    }

    CreateGameDTO(const std::string& gn, MapName m):
        DTO(DTOSerial::LobbyCommands::CREATE_GAME), game_name(gn), map(m) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(game_name.size()));
        out.insert(out.end(), game_name.begin(), game_name.end());
        out.push_back(static_cast<uint8_t>(map));
    }

    const std::string& get_game_name() const { return game_name; }
    MapName get_map() const { return map; }
};

#endif
