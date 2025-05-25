#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

namespace PlayerCommandSerial {
constexpr uint8_t MOVE = 0x6D;    // m
constexpr uint8_t ATTACK = 0x61;  // a
};  // namespace PlayerCommandSerial

namespace CardinalSerial {
constexpr uint8_t N = 0x00;
constexpr uint8_t NE = 0x01;
constexpr uint8_t E = 0x02;
constexpr uint8_t SE = 0x03;
constexpr uint8_t S = 0x04;
constexpr uint8_t SW = 0x05;
constexpr uint8_t W = 0x06;
constexpr uint8_t NW = 0x07;
};  // namespace CardinalSerial

namespace Message {
constexpr int LenBytes = 2;  // vamos a mandar algo mas grande que 255 bytes?
constexpr int MaxLen = 256;
};  // namespace Message

#endif
