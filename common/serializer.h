#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <string>

#include "direction.h"

class Serializer {
public:
    static std::string serialize_move(const Direction& dir);
    static std::string serialize_attack(const float& angle);
};

#endif
