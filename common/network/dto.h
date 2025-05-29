#ifndef DTO_H
#define DTO_H

#include "../position.h"
#include "../direction.h"

#include <cstdint>
#include <vector>
#include <iterator>
#include <bit>
#include <arpa/inet.h>
#include <cstring>

class DTO {
protected:
    std::vector<uint8_t> bytes;

    DTO(const uint8_t type) { bytes.push_back(type); }

    std::vector<uint8_t> serialize_float(const float& n) {
        auto srlzd_n = std::bit_cast<uint32_t>(n);
        srlzd_n = htonl(srlzd_n);
        std::vector<uint8_t> bytes(sizeof(srlzd_n));
        std::memcpy(bytes.data(), &srlzd_n, sizeof(srlzd_n));
        return bytes;
    }

    std::vector<uint8_t> serialize_tuple(const float& x, const float& y) {
        std::vector<uint8_t> srlzd_tuple;
        auto srlzd_x = serialize_float(x);
        auto srlzd_y = serialize_float(y);
        srlzd_tuple.insert(srlzd_tuple.end(), srlzd_x.begin(), srlzd_x.end());
        srlzd_tuple.insert(srlzd_tuple.end(), srlzd_y.begin(), srlzd_y.end());
        return srlzd_tuple;
    }

    std::vector<uint8_t> serialize_pos(const Position& pos) { return serialize_tuple(pos.x, pos.y); }

    std::vector<uint8_t> serialize_dir(const Direction& dir) { return serialize_tuple(dir.x, dir.y); }

public:
    DTO(const std::vector<uint8_t>&& bytes): bytes(std::move(bytes)) {}


    const std::vector<uint8_t>& serialize() const { return bytes; }

    uint8_t get_type() const { return bytes[0]; }

    const std::vector<uint8_t>& get_data() const { return bytes; }


    DTO(const DTO&) = delete;
    DTO& operator=(const DTO&) = delete;

    DTO(DTO&&) = default;
    DTO& operator=(DTO&&) = default;

    virtual ~DTO() = default;
};

#endif
