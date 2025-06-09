#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

namespace Message {
constexpr int LenBytes = 2;  // vamos a mandar algo mas grande que 255 bytes?
constexpr int MaxLen = 256; // <= 65535
};  // namespace Message

namespace DTOSerial {
    namespace PlayerCommands {
    constexpr uint8_t MOVE = 0x6D;    // m
    constexpr uint8_t ATTACK = 0x61;  // a
    constexpr uint8_t SNAPSHOT = 0x62; // NOTE alepaff: 98 Totalmente arbitrario, solo para que compile
    };  // namespace PlayerCommands
};  // namespace DTO

#endif
