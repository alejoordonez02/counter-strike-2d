#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

namespace PlayerCommandSerial {
constexpr uint8_t MOVE = 0x6D;    // m
constexpr uint8_t ATTACK = 0x61;  // a
};  // namespace PlayerCommandSerial

namespace Message {
constexpr int LenBytes = 2;  // vamos a mandar algo mas grande que 255 bytes?
constexpr int MaxLen = 256;
};  // namespace Message

#endif
