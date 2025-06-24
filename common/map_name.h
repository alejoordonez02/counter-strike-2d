#ifndef MAP_NAME_H
#define MAP_NAME_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include "map_list.h"
#include "common/network/protocol.h"

enum class MapName : uint8_t {
    #define X(name, lowercase) name = MapSerial::name,
        MAP_LIST
    #undef X
};

inline std::string mapNameToString(MapName map) {
    switch (map) {
        #define X(name, lowercase) \
                case MapName::name: \
                    return lowercase;
            MAP_LIST
        #undef X
        default:
            return "unknown";
    }
}

#endif