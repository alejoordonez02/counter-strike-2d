#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>

#include "../player_commands/attack.h"
#include "../player_commands/move.h"

class Serializer {
private:
    static std::vector<uint8_t> serialize(const float& n);
    static std::vector<uint8_t> serialize(const float& x, const float& y);
    static std::vector<uint8_t> serialize(const Position& pos);
    static std::vector<uint8_t> serialize(const Direction& dir);

public:
    static std::vector<uint8_t> serialize(const Move& move);
    static std::vector<uint8_t> serialize(const Attack& attack);
};

#endif
