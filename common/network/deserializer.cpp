#include "deserializer.h"

#include <cstdint>
#include <map>
#include <stdexcept>

#include <arpa/inet.h>

#include "../direction.h"
#include "../player_commands/attack.h"
#include "../player_commands/command.h"
#include "../player_commands/move.h"

#include "protocol.h"

namespace {
inline const std::map<uint8_t, Direction> srl_to_dir = {
        {DirectionSerial::N, Direction::N}, {DirectionSerial::NE, Direction::NE},
        {DirectionSerial::E, Direction::E}, {DirectionSerial::SE, Direction::SE},
        {DirectionSerial::S, Direction::S}, {DirectionSerial::SW, Direction::SW},
        {DirectionSerial::W, Direction::W}, {DirectionSerial::NW, Direction::NW}};
};

std::unique_ptr<Move> Deserializer::deserialize_move_command(const std::string& srlzd_cmd) {
    return std::make_unique<Move>(srl_to_dir.at(srlzd_cmd[1]));
}

std::unique_ptr<Attack> Deserializer::deserialize_attack_command(const std::string& srlzd_cmd) {
    uint32_t angle = static_cast<uint32_t>(srlzd_cmd[1]);
    angle = ntohl(angle);
    return std::make_unique<Attack>(angle);
}

std::unique_ptr<Command> Deserializer::deserialize_command(const std::string& srlzd_cmd) {
    switch (srlzd_cmd[0]) {
        case PlayerCommandSerial::MOVE:
            return deserialize_move_command(srlzd_cmd);
        case PlayerCommandSerial::ATTACK:
            return deserialize_attack_command(srlzd_cmd);
        default:
            throw std::runtime_error("Deserialization error: unknown player command serial");
    }
}
