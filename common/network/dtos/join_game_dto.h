#ifndef COMMON_NETWORK_DTOS_JOIN_GAME_DTO_H
#define COMMON_NETWORK_DTOS_JOIN_GAME_DTO_H

#include <string>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/team_name.h"

class JoinGameDTO: public DTO {
private:
    std::string game_name;
    TeamName team;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        game_name = deserialize_string_from(in);
        team = static_cast<TeamName>(*in++);
    }

public:
    explicit JoinGameDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        auto payload_it = payload.begin();
        deserialize_from(payload_it);
    }

    explicit JoinGameDTO(std::vector<uint8_t>::iterator& in):
            DTO(DTOSerial::LobbyCommands::JOIN_GAME) {
        deserialize_from(in);
    }

    explicit JoinGameDTO(const std::string& gn, TeamName t):
        DTO(DTOSerial::LobbyCommands::JOIN_GAME), game_name(gn), team(t) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_string_into(out, game_name);
        out.push_back(static_cast<uint8_t>(team));
    }

    const std::string& get_game_name() const { return game_name; }
    TeamName get_team() const { return team; }

    ~JoinGameDTO() = default;
};

#endif
