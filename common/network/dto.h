#ifndef DTO_H
#define DTO_H

#include "../position.h"
#include "../direction.h"

#include <cstdint>
#include <vector>
#include <bit>
#include <arpa/inet.h>
#include <cstring>

class DTO {
protected:
    std::vector<uint8_t> payload;
    bool _is_serialized;

    DTO(): _is_serialized(true) {}
    explicit DTO(const uint8_t type): _is_serialized(false) { payload.push_back(type); }

    virtual void deserialize() = 0;

public:
    uint8_t get_type() const { return payload[0]; }
    virtual const std::vector<uint8_t>& serialize() = 0;

    DTO(const DTO&) = delete;
    DTO& operator=(const DTO&) = delete;

    DTO(DTO&&) = default;
    DTO& operator=(DTO&&) = default;

    virtual ~DTO() = default;

protected:
    // serialization

    void serialize_float(const float& n);
    void serialize_tuple(const float& x, const float& y);
    void serialize_pos(const Position& pos);
    void serialize_dir(const Direction& dir);

    // deserialization

    float deserialize_float(int& i);
    Position deserialize_pos(int& i);
    Direction deserialize_dir(int& i);
};

#endif
