#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <string>

#include "../player_commands.h"

namespace { // poner en archivo protocol?
constexpr uint8_t MOVE_CMD = 0x6D; // m
constexpr uint8_t ATTACK_CMD = 0x61; // a
// ...
}

class Serializer {
public:
    Serializer() = default;


    std::string serialize(const Move& move) {}

    std::string serialize(const Attack& attack) {}

    // ...

    // std::string serialize(const GameState&) {}

    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;

    Serializer(Serializer&&) = default;
    Serializer& operator=(Serializer&&) = default;

    ~Serializer() = default;
};

#endif


// private:
//     std::string serialize_number(const float& n);

