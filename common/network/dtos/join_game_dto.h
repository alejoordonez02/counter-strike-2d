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

    void deserialize() override {
        int i = 1;
        uint8_t len = payload[i++];
        game_name.assign(payload.begin() + i, payload.begin() + i + len);
        i += len;
        team = static_cast<TeamName>(payload[i++]);
    }

public:
    explicit JoinGameDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    explicit JoinGameDTO(const std::string& gn, TeamName t):
        DTO(DTOSerial::LobbyCommands::JOIN_GAME), game_name(gn), team(t) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        out.push_back(static_cast<uint8_t>(game_name.size()));
        out.insert(out.end(), game_name.begin(), game_name.end());
        out.push_back(static_cast<uint8_t>(team));
    }

    const std::string& get_game_name() const { return game_name; }
    TeamName get_team() const { return team; }
};

#endif
