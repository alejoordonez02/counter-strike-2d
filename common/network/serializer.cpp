#include "serializer.h"

#include <cstdint>
#include <cstring>
#include <vector>

#include <arpa/inet.h>

#include "player_commands.h"
#include "protocol.h"


std::vector<uint8_t> Serializer::serialize_number(const float& n) {
    uint32_t tmp_n = std::bit_cast<uint32_t>(n);
    tmp_n = htonl(tmp_n);
    std::vector<uint8_t> srlzd_n(sizeof(tmp_n));
    std::memcpy(srlzd_n.data(), &tmp_n, sizeof(tmp_n));
    return srlzd_n;
}

std::vector<uint8_t> Serializer::serialize(const Move& move) {
    std::vector<uint8_t> srlzd_move;
    std::vector<uint8_t> srlzd_direction = serialize_number(move.get_dir().t);
    srlzd_move.push_back(static_cast<uint8_t>(PlayerCommandSerial::MOVE));
    srlzd_move.insert(srlzd_move.end(), srlzd_direction.begin(), srlzd_direction.end());
    return srlzd_move;
}

std::vector<uint8_t> Serializer::serialize(const Attack& attack) {
    std::vector<uint8_t> srlzd_attack;
    auto pos = attack.get_pos();
    std::vector<uint8_t> srlzd_x = serialize_number(pos.x);
    std::vector<uint8_t> srlzd_y = serialize_number(pos.y);
    srlzd_attack.push_back(static_cast<uint8_t>(PlayerCommandSerial::MOVE));
    srlzd_attack.insert(srlzd_attack.end(), srlzd_x.begin(), srlzd_x.end());
    srlzd_attack.insert(srlzd_attack.end(), srlzd_y.begin(), srlzd_y.end());
    return srlzd_attack;
}
