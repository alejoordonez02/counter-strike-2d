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
    static const std::unordered_map<MapName, std::string> mapNames = {
        {MapName::DUST, "Dust II"},
        {MapName::AZTEC, "Aztec"},
        {MapName::NUKE, "Nuke"}
    };
    const auto it = mapNames.find(map);
    return it != mapNames.end() ? it->second : "Desconocido";
}

#endif