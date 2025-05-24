#include "deserializer.h"

#include <bit>
#include <cstdint>
#include <cstring>
#include <map>
#include <stdexcept>

#include <arpa/inet.h>

#include "../direction.h"
#include "../player_commands/attack.h"
#include "../player_commands/command.h"
#include "../player_commands/move.h"
#include "../position.h"

#include "protocol.h"

namespace {
inline const std::map<uint8_t, Direction> srl_to_dir = {
        {DirectionSerial::N, Direction::N}, {DirectionSerial::NE, Direction::NE},
        {DirectionSerial::E, Direction::E}, {DirectionSerial::SE, Direction::SE},
        {DirectionSerial::S, Direction::S}, {DirectionSerial::SW, Direction::SW},
        {DirectionSerial::W, Direction::W}, {DirectionSerial::NW, Direction::NW}};
};

/*
 * Deserialize float
 * */
float Deserializer::deserialize_float(const std::vector<uint8_t>& srlzd_n) {
    uint32_t dsrlzd_n;
    std::memcpy(&dsrlzd_n, srlzd_n.data(), sizeof(dsrlzd_n));
    dsrlzd_n = ntohl(dsrlzd_n);
    return std::bit_cast<float>(dsrlzd_n);
}

/*
 * Deserialize position
 * */
Position Deserializer::deserialize_position(const std::vector<uint8_t>& srlzd_pos) {
    float x = deserialize_float(srlzd_pos);  // first bytes of pos are srlzd_x
    std::vector<uint8_t> srlzd_y = std::vector<uint8_t>(srlzd_pos.begin() + 4, srlzd_pos.end());
    float y = deserialize_float(srlzd_y);
    return Position(x, y);
}

/*
 * Deserialize player commands
 * */
std::unique_ptr<Move> Deserializer::deserialize_move_command(
        const std::vector<uint8_t>& srlzd_cmd) {
    return std::make_unique<Move>(srl_to_dir.at(srlzd_cmd[1]));
}

std::unique_ptr<Attack> Deserializer::deserialize_attack_command(
        const std::vector<uint8_t>& srlzd_cmd) {
    std::vector<uint8_t> srlzd_pos = std::vector<uint8_t>(srlzd_cmd.begin() + 1, srlzd_cmd.end());
    auto pos = deserialize_position(srlzd_pos);
    return std::make_unique<Attack>(pos);
}

std::unique_ptr<Command> Deserializer::deserialize_command(const std::vector<uint8_t>& srlzd_cmd) {
    switch (srlzd_cmd[0]) {
        case PlayerCommandSerial::MOVE:
            return deserialize_move_command(srlzd_cmd);
        case PlayerCommandSerial::ATTACK:
            return deserialize_attack_command(srlzd_cmd);
        default:
            throw std::runtime_error("Deserialization error: unknown player command serial");
    }
}
