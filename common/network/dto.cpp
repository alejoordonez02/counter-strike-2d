#include "common/network/dto.h"

#include <cstring>
#include <bit>

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

void DTO::serialize_tuple_into(std::vector<uint8_t>& out, const float& x,
                               const float& y) {
    serialize_float_into(out, x);
    serialize_float_into(out, y);
}

void DTO::serialize_pos_into(std::vector<uint8_t>& out, const Position& pos) {
    serialize_tuple_into(out, pos.x, pos.y);
}

void DTO::serialize_dir_into(std::vector<uint8_t>& out, const Direction& dir) {
    serialize_tuple_into(out, dir.x, dir.y);
}

void DTO::serialize_string_into(std::vector<uint8_t>& out, const std::string& str) {
    serialize_uint16_into(out, str.size());
    out.insert(out.end(), str.begin(), str.end());
}

void DTO::serialize_uint16_into(std::vector<uint8_t>& out, uint16_t n) {
    uint16_t n_be = htons(n);
    std::vector<uint8_t> bytes(sizeof(n_be));
    std::memcpy(bytes.data(), &n_be, sizeof(n_be));
    out.insert(out.end(), bytes.begin(), bytes.end());
}

void DTO::serialize_int_into(std::vector<uint8_t>& out, int n) {
    int n_be = htonl(n);
    std::vector<uint8_t> bytes(sizeof(n_be));
    std::memcpy(bytes.data(), &n_be, sizeof(n_be));
    out.insert(out.end(), bytes.begin(), bytes.end());
}


// deserialization

float DTO::deserialize_float_from(std::vector<uint8_t>::iterator& in) {
    uint32_t dsrlzd_n;
    std::memcpy(&dsrlzd_n, &*in, sizeof(dsrlzd_n));
    in += sizeof(dsrlzd_n);
    dsrlzd_n = ntohl(dsrlzd_n);
    return std::bit_cast<float>(dsrlzd_n);
}

Position DTO::deserialize_pos_from(std::vector<uint8_t>::iterator& in) {
    float x = deserialize_float_from(in);
    float y = deserialize_float_from(in);
    return Position(x, y);
}

Direction DTO::deserialize_dir_from(std::vector<uint8_t>::iterator& in) {
    float x = deserialize_float_from(in);
    float y = deserialize_float_from(in);
    return Direction(x, y);
}

std::string DTO::deserialize_string_from(std::vector<uint8_t>::iterator& in) {
    uint16_t str_size = deserialize_uint16_from(in);
    std::string str(str_size, '0');
    std::memcpy(str.data(), &*in, str_size);
    in += str_size;
    return str;
}

uint16_t DTO::deserialize_uint16_from(std::vector<uint8_t>::iterator& in) {
    uint16_t n = 0;
    std::memcpy(&n, &*in, sizeof(n));
    n = ntohs(n);
    in += sizeof(n);
    return n;
}

int DTO::deserialize_int_from(std::vector<uint8_t>::iterator& in) {
    int n = 0;
    std::memcpy(&n, &*in, sizeof(n));
    n = ntohl(n);
    in += sizeof(n);
    return n;
}
