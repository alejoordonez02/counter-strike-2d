#ifndef GAME_DETAILS_DTO_H
#define GAME_DETAILS_DTO_H

#include <string>
#include <vector>
#include <cstdint>

#include "../dto.h"
#include "../protocol.h"

class GameDetailsDTO: public DTO {
private:
    std::string name;
    uint8_t n_players;
    std::string map_name;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        name = deserialize_string(i);
        n_players = payload[i++];
        map_name = deserialize_string(i);
    }

public:
    explicit GameDetailsDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    explicit GameDetailsDTO(const std::string& name, uint8_t n_plys, const std::string& map_name): 
            DTO(DTOSerial::GAME_DETAILS), name(name), n_players(n_plys), map_name(map_name) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_string_into(out, name);
        out.push_back(n_players);
        serialize_string_into(out, map_name);
    }

    ~GameDetailsDTO() = default;
};

#endif
