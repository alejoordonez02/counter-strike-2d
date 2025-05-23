#include "serializer.h"

#include <bit>
#include <cstdint>
#include <cstring>
#include <map>
#include <vector>

#include <arpa/inet.h>

#include "../direction.h"
#include "../player_commands/attack.h"
#include "../player_commands/move.h"

#include "protocol.h"

namespace {
inline const std::map<Direction, uint8_t> dir_to_srl = {
        {Direction::N, DirectionSerial::N}, {Direction::NE, DirectionSerial::NE},
        {Direction::E, DirectionSerial::E}, {Direction::SE, DirectionSerial::SE},
        {Direction::S, DirectionSerial::S}, {Direction::SW, DirectionSerial::SW},
        {Direction::W, DirectionSerial::W}, {Direction::NW, DirectionSerial::NW}};
};

/*
 * Serialize float
 * */
std::vector<uint8_t> Serializer::serialize(const float& n) {
    auto srlzd_n = std::bit_cast<uint32_t>(n);
    srlzd_n = htonl(srlzd_n);
    std::vector<uint8_t> bytes(sizeof(srlzd_n));
    std::memcpy(bytes.data(), &srlzd_n, sizeof(srlzd_n));
    return bytes;
}

/*
 * Serialize player commands
 * */
std::vector<uint8_t> Serializer::serialize(const Move& move) {
    return {PlayerCommandSerial::MOVE, dir_to_srl.at(move.get_dir())};
}

std::vector<uint8_t> Serializer::serialize(const Attack& attack) {
    std::vector<uint8_t> srlzd_attack;

    auto pos = attack.get_position();
    auto srlzd_x = serialize(pos.x);
    auto srlzd_y = serialize(pos.y);

    srlzd_attack.push_back(PlayerCommandSerial::ATTACK);
    srlzd_attack.insert(srlzd_attack.end(), srlzd_x.begin(), srlzd_x.end());
    srlzd_attack.insert(srlzd_attack.end(), srlzd_y.begin(), srlzd_y.end());

    return srlzd_attack;
}
