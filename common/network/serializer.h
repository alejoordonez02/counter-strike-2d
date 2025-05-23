#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <sstream>
#include <string>

#include "../player_commands.h"

class Serializer {
private:
    void write_number(std::ostringstream oss, uint16_t n);
    // void write_number(std::ostringstream oss, float n);

public:
    Serializer() = default;


    std::string serialize(const Move& move) {}

    std::string serialize(const Attack& attack) {}

    // ...

    // std::string serialize(const GameStateInfo&) {}

    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;

    Serializer(Serializer&&) = default;
    Serializer& operator=(Serializer&&) = default;

    ~Serializer() = default;
};

#endif


// private:
//     std::string serialize_number(const float& n);
