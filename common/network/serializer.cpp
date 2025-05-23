#include "serializer.h"

#include <cstdint>
#include <cstring>
#include <sstream>

#include <arpa/inet.h>

#include "player_commands.h"
#include "protocol.h"


// std::vector<uint8_t> Serializer::serialize_number(const float& n) {
//     uint32_t tmp_n = std::bit_cast<uint32_t>(n);
//     tmp_n = htonl(tmp_n);
//     std::vector<uint8_t> srlzd_n(sizeof(tmp_n));
//     std::memcpy(srlzd_n.data(), &tmp_n, sizeof(tmp_n));
//     return srlzd_n;
// }

void Serializer::write_number(std::ostringstream oss, uint16_t n) {
    uint16_t s = htons(n);
    oss.write((const char*)&s, sizeof(s));
}

std::string Serializer::serialize(const Move& move) {
    std::ostringstream oss;

    oss.put(PlayerCommandSerial::MOVE);
    oss.put(move.get_player_id());

    switch (move.get_dir()) {
        case N:
            oss.put(DirectionSerial::N);
            break;
        case NE:
            oss.put(DirectionSerial::NE);
            break;
        case E:
            oss.put(DirectionSerial::E);
            break;
        case SE:
            oss.put(DirectionSerial::SE);
            break;
        case S:
            oss.put(DirectionSerial::S);
            break;
        case SW:
            oss.put(DirectionSerial::SW);
            break;
        case W:
            oss.put(DirectionSerial::W);
            break;
        case NW:
            oss.put(DirectionSerial::NW);
            break;
    }

    return oss.str();
}

std::string Serializer::serialize(const Attack& attack) {}
