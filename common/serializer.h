#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <vector>

#include "command.h"

class Serializer {
private:
    static std::vector<uint8_t> serialize_number(const float& n);

public:
    static std::vector<uint8_t> serialize_move_cmd(const Move& move);
    static std::vector<uint8_t> serialize_attack_cmd(const Attack& attack);
};

#endif
