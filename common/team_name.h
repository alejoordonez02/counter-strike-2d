#ifndef TEAM_NAME_H
#define TEAM_NAME_H

#include <cstdint>

#include "common/network/protocol.h"

enum class TeamName : uint8_t {
    TERRORIST = GameSerial::TERRORIST,
    COUNTER_TERRORIST = GameSerial::COUNTER_TERRORIST
};

#endif
