#ifndef COMMON_NETWORK_DTOS_JOIN_GAME_DTO_H
#define COMMON_NETWORK_DTOS_JOIN_GAME_DTO_H

#include <string>
#include <vector>

#include "common/network/dto.h"
#include "common/network/protocol.h"

class JoinGameDTO: public DTO {
private:
    std::string game_name;

    void deserialize_from(std::vector<uint8_t>::iterator& in) override {
        in++;  // skip 1st byte (DTO type)
        game_name = deserialize_string_from(in);
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

    explicit JoinGameDTO(const std::string& gn):
        DTO(DTOSerial::LobbyCommands::JOIN_GAME), game_name(gn) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_string_into(out, game_name);
    }

    const std::string& get_game_name() const { return game_name; }

    ~JoinGameDTO() = default;
};

#endif
