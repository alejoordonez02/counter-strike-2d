#include "dto.h"

const std::vector<uint8_t>& DTO::serialize() {
    if (not _is_serialized) {
        serialize_into(payload);
        _is_serialized = true;    
    }
    return payload;
}

// serialization

void DTO::serialize_float_into(std::vector<uint8_t>& out, const float& n) {
    auto srlzd_n = std::bit_cast<uint32_t>(n);
    srlzd_n = htonl(srlzd_n);
    std::vector<uint8_t> bytes(sizeof(srlzd_n));
    std::memcpy(bytes.data(), &srlzd_n, sizeof(srlzd_n));
    out.insert(out.end(), bytes.begin(), bytes.end());
}

void DTO::serialize_tuple_into(std::vector<uint8_t>& out, const float& x, const float& y) {
    serialize_float_into(out, x);
    serialize_float_into(out, y);
}

void DTO::serialize_pos_into(std::vector<uint8_t>& out, const Position& pos) {
    serialize_tuple_into(out, pos.x, pos.y);
}

void DTO::serialize_dir_into(std::vector<uint8_t>& out, const Direction& dir) {
    serialize_tuple_into(out, dir.x, dir.y);
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