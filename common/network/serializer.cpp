#include "serializer.h"

#include <bit>
#include <cstdint>
#include <cstring>
#include <vector>

#include <arpa/inet.h>

#include "../direction.h"
#include "../player_commands/attack.h"
#include "../player_commands/move.h"

#include "protocol.h"

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
 * Serialize tuples
 * */
std::vector<uint8_t> Serializer::serialize(const float& x, const float& y) {
    std::vector<uint8_t> srlzd_tuple;
    auto srlzd_x = serialize(x);
    auto srlzd_y = serialize(y);
    srlzd_tuple.insert(srlzd_tuple.end(), srlzd_x.begin(), srlzd_x.end());
    srlzd_tuple.insert(srlzd_tuple.end(), srlzd_y.begin(), srlzd_y.end());
    return srlzd_tuple;
}

std::vector<uint8_t> Serializer::serialize(const Position& pos) { return serialize(pos.x, pos.y); }

std::vector<uint8_t> Serializer::serialize(const Direction& dir) { return serialize(dir.x, dir.y); }

/*
 * Serialize player commands
 * */
std::vector<uint8_t> Serializer::serialize(const Move& move) {
    std::vector<uint8_t> srlzd_move;
    auto dir = move.get_direction();
    auto srlzd_dir = serialize(dir);
    srlzd_move.push_back(PlayerCommandSerial::MOVE);
    srlzd_move.insert(srlzd_move.end(), srlzd_dir.begin(), srlzd_dir.end());
    return srlzd_move;
}

std::vector<uint8_t> Serializer::serialize(const Attack& attack) {
    std::vector<uint8_t> srlzd_attack;
    auto pos = attack.get_position();
    auto srlzd_pos = serialize(pos);
    srlzd_attack.push_back(PlayerCommandSerial::ATTACK);
    srlzd_attack.insert(srlzd_attack.end(), srlzd_pos.begin(), srlzd_pos.end());
    return srlzd_attack;
}
