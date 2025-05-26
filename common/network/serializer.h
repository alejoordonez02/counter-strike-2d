#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <sstream>
#include <string>

#include "../player_commands/attack.h"
#include "../player_commands/move.h"
#include "../serializable.h"

class Serializer {
private:
    static std::vector<uint8_t> serialize(const float& n);

public:
    static std::vector<uint8_t> serialize(const Move& move);
    static std::vector<uint8_t> serialize(const Attack& attack);
};

#endif
