#include "cmd_deserializer.h"

#include <bit>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include <arpa/inet.h>

#include "../direction.h"
#include "../player_commands/attack.h"
#include "../player_commands/command.h"
#include "../player_commands/move.h"
#include "../position.h"

#include "protocol.h"

/*
 * Deserialize float
 * */
float CmdDeserializer::deserialize_float(const std::vector<uint8_t>& srlzd_n) {
    uint32_t dsrlzd_n;
    std::memcpy(&dsrlzd_n, srlzd_n.data(), sizeof(dsrlzd_n));
    dsrlzd_n = ntohl(dsrlzd_n);
    return std::bit_cast<float>(dsrlzd_n);
}

/*
 * Deserialize tuples
 * */
Position CmdDeserializer::deserialize_position(const std::vector<uint8_t>& srlzd_pos) {
    float x = deserialize_float(srlzd_pos);  // first bytes of pos are srlzd_x
    std::vector<uint8_t> srlzd_y = std::vector<uint8_t>(srlzd_pos.begin() + 4, srlzd_pos.end());
    float y = deserialize_float(srlzd_y);
    return Position(x, y);
}

Direction Deserializer::deserialize_direction(const std::vector<uint8_t>& srlzd_dir) {
    float x = deserialize_float(srlzd_dir);  // first bytes of pos are srlzd_x
    std::vector<uint8_t> srlzd_y = std::vector<uint8_t>(srlzd_dir.begin() + 4, srlzd_dir.end());
    float y = deserialize_float(srlzd_y);
    return Direction(x, y);
}

/*
 * Deserialize player commands
 * */
std::unique_ptr<Move> CmdDeserializer::deserialize_move_command(
        const std::vector<uint8_t>& srlzd_cmd) {
    std::vector<uint8_t> srlzd_dir = std::vector<uint8_t>(srlzd_cmd.begin() + 1, srlzd_cmd.end());
    auto dir = deserialize_direction(srlzd_dir);
    return std::make_unique<Move>(dir);
}

std::unique_ptr<Attack> CmdDeserializer::deserialize_attack_command(
        const std::vector<uint8_t>& srlzd_cmd) {
    std::vector<uint8_t> srlzd_pos = std::vector<uint8_t>(srlzd_cmd.begin() + 1, srlzd_cmd.end());
    auto pos = deserialize_position(srlzd_pos);
    return std::make_unique<Attack>(pos);
}

std::unique_ptr<Command> CmdDeserializer::deserialize_command(const std::vector<uint8_t>& srlzd_cmd) {
    switch (srlzd_cmd[0]) {
        case PlayerCommandSerial::MOVE:
            return deserialize_move_command(srlzd_cmd);
        case PlayerCommandSerial::ATTACK:
            return deserialize_attack_command(srlzd_cmd);
        default:
            throw std::runtime_error("Deserialization error: unknown player command serial");
    }
}
