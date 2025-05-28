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

namespace DirectionSerial {
constexpr uint8_t N = 0x00;
constexpr uint8_t NE = 0x01;
constexpr uint8_t E = 0x02;
constexpr uint8_t SE = 0x03;
constexpr uint8_t S = 0x04;
constexpr uint8_t SW = 0x05;
constexpr uint8_t W = 0x06;
constexpr uint8_t NW = 0x07;
};  // namespace DirectionSerial

#endif
