#include "dto.h"

// serialization

void DTO::serialize_float(const float& n) {
    auto srlzd_n = std::bit_cast<uint32_t>(n);
    srlzd_n = htonl(srlzd_n);
    std::vector<uint8_t> bytes(sizeof(srlzd_n));
    std::memcpy(bytes.data(), &srlzd_n, sizeof(srlzd_n));
    payload.insert(payload.end(), bytes.begin(), bytes.end());
}

void DTO::serialize_tuple(const float& x, const float& y) {
    serialize_float(x);
    serialize_float(y);
}

void DTO::serialize_pos(const Position& pos) {
    serialize_tuple(pos.x, pos.y);
}

void DTO::serialize_dir(const Direction& dir) {
    serialize_tuple(dir.x, dir.y);
}


// deserialization

float DTO::deserialize_float(int& i) {
    uint32_t dsrlzd_n;
    std::memcpy(&dsrlzd_n, payload.data() + i, sizeof(dsrlzd_n));
    i += sizeof(dsrlzd_n);
    dsrlzd_n = ntohl(dsrlzd_n);
    return std::bit_cast<float>(dsrlzd_n);
}

Position DTO::deserialize_pos(int& i) {
    float x = deserialize_float(i);
    float y = deserialize_float(i);
    return Position(x, y);
}

Direction DTO::deserialize_dir(int& i) {
    float x = deserialize_float(i);
    float y = deserialize_float(i);
    return Direction(x, y);
}