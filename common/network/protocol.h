#ifndef COMMON_NETWORK_PROTOCOL_H
#define COMMON_NETWORK_PROTOCOL_H

#include <cstdint>

#include "common/map_list.h"

namespace Message {
constexpr int LenBytes = 2;  // vamos a mandar algo mas grande que 255 bytes?
constexpr int MaxLen = 256;  // <= 65535
};  // namespace Message

namespace MapSerial {
enum : uint8_t {
#define X(name) name,
    MAP_LIST
#undef X
};
};  // namespace MapSerial

namespace DTOSerial {
constexpr uint8_t GAME_DETAILS = 0x47;  // G - 71
constexpr uint8_t SNAPSHOT = 0x53;  // S - 83
constexpr uint8_t PLAYER_PRIVATE = 0x49;  // I - 73
constexpr uint8_t PLAYER = 0x50;  // P - 80
constexpr uint8_t WEAPON = 0x57;  // W - 87
namespace PlayerCommands {
constexpr uint8_t AIM = 0xD7;           // × - 215
constexpr uint8_t START_MOVING = 0x6D;  // m - 109
constexpr uint8_t STOP_MOVING = 0x6E;  // n - 110
constexpr uint8_t START_ATTACKING = 0x61;  // a - 97
constexpr uint8_t STOP_ATTACKING = 0x62;  // b - 98
constexpr uint8_t START_PLANTING = 0x70;  // p - 112
constexpr uint8_t STOP_PLANTING = 0x71;  // q - 113
constexpr uint8_t CHANGE_WEAPON = 0x77;  // w - 119
};  // namespace PlayerCommands
namespace LobbyCommands {
constexpr uint8_t CHANGE_USERNAME = 0x55;  // U - 85
constexpr uint8_t LIST_GAMES = 0x4C;       // L - 76
constexpr uint8_t CREATE_GAME = 0x43;      // C - 67
constexpr uint8_t JOIN_GAME = 0x4A;        // J - 74
constexpr uint8_t SUCCESS = 0x53;          // S - 83
constexpr uint8_t FAILURE = 0x46;          // F - 70
constexpr uint8_t EXIT_SERVER = 0x45;      // E - 69
};  // namespace LobbyCommands
namespace GameState {
// TODO: SnapshotDTO
}
};  // namespace DTOSerial

#endif
