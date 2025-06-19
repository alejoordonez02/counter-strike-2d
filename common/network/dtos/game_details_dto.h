#ifndef GAME_DETAILS_DTO_H
#define GAME_DETAILS_DTO_H

#include <string>
#include <vector>
#include <cstdint>

#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "common/map_name.h"

class GameDetailsDTO: public DTO {
private:
    std::string name;
    uint8_t tt_count;
    uint8_t ct_count;
    MapName map_name;
    bool _is_joinable;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        name = deserialize_string(i);
        tt_count = payload[i++];
        ct_count = payload[i++];
        map_name = static_cast<MapName>(payload[i++]);
        _is_joinable = payload[i++];
    }

public:
    explicit GameDetailsDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    GameDetailsDTO(const std::string& name, uint8_t tt_cnt, uint8_t ct_cnt, MapName mn, bool is_j): 
            DTO(DTOSerial::GAME_DETAILS), name(name), tt_count(tt_cnt), ct_count(ct_cnt), map_name(mn), _is_joinable(is_j) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_string_into(out, name);
        out.push_back(tt_count);
        out.push_back(ct_count);
        out.push_back(static_cast<uint8_t>(map_name));
        out.push_back(_is_joinable);
    }

    // get_name
    // get_tt_count
    // get_ct_count
    // get_map_name
    // get_is_joinable

    ~GameDetailsDTO() = default;
};

#endif
