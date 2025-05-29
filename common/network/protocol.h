#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

namespace Message {
constexpr int LenBytes = 2;  // vamos a mandar algo mas grande que 255 bytes?
constexpr int MaxLen = 256; // <= 65535
};  // namespace Message

namespace DTOtypeSerial {
constexpr uint8_t COMMAND = 0x43;    // C
constexpr uint8_t GAME_STATE = 0x47;  // G
};  // namespace DTOtypeSerial

namespace PlayerCommandSerial {
constexpr uint8_t MOVE = 0x6D;    // m
constexpr uint8_t ATTACK = 0x61;  // a
};  // namespace PlayerCommandSerial

#endif
