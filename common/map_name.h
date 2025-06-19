#ifndef MAP_NAME_H
#define MAP_NAME_H

#include <cstdint>

#include "map_list.h"
#include "network/protocol.h"

enum class MapName : uint8_t {
#define X(name) name = MapSerial::name,
    MAP_LIST
#undef X
};

#endif
