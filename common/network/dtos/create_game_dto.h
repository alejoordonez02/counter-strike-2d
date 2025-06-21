#ifndef COMMON_NETWORK_DTOS_CREATE_GAME_DTO_H
#define COMMON_NETWORK_DTOS_CREATE_GAME_DTO_H

#include <string>
#include <vector>

#include "common/map_name.h"
#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/team_name.h"

class CreateGameDTO: public DTO {
private:
    std::string game_name;
    MapName map;
    TeamName team;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        game_name = deserialize_string_from(in);
        map = static_cast<MapName>(*in++);
        team = static_cast<TeamName>(*in++);
    }

public:
    explicit CreateGameDTO(std::vector<uint8_t>&& bytes):
            DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit CreateGameDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::LobbyCommands::CREATE_GAME) {
        deserialize_from(in);
    }

    CreateGameDTO(const std::string& gn, MapName m, TeamName t):
        DTO(DTOSerial::LobbyCommands::CREATE_GAME), game_name(gn), map(m), team(t) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_string_into(out, game_name);
        out.push_back(static_cast<uint8_t>(map));
        out.push_back(static_cast<uint8_t>(team));
    }

    const std::string& get_game_name() const { return game_name; }
    MapName get_map() const { return map; }
    TeamName get_team() const { return team; }

    ~CreateGameDTO() = default;
};

#endif
