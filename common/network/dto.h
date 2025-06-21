#ifndef COMMON_NETWORK_DTO_H
#define COMMON_NETWORK_DTO_H

#include <cstdint>
#include <utility>
#include <vector>
#include <string>

#include <arpa/inet.h>

#include "common/direction.h"
#include "common/position.h"

class DTO {
protected:
    uint8_t type;
    std::vector<uint8_t> payload;
    bool _is_serialized;

    explicit DTO(std::vector<uint8_t>&& bytes):
            type(bytes[0]), payload(std::move(bytes)), _is_serialized(true) {}
    explicit DTO(const uint8_t type): type(type), _is_serialized(false) {}

    virtual void deserialize_from(std::vector<uint8_t>::iterator&) = 0;

public:
    uint8_t get_type() const { return type; }
    const std::vector<uint8_t>& serialize();
    virtual void serialize_into(std::vector<uint8_t>& out) = 0;

    DTO(const DTO&) = delete;
    DTO& operator=(const DTO&) = delete;

    DTO(DTO&&) = default;
    DTO& operator=(DTO&&) = default;

    virtual ~DTO() = default;

protected:
    // serialization

    void serialize_float_into(std::vector<uint8_t>& out, const float& n);
    void serialize_tuple_into(std::vector<uint8_t>& out, const float& x,
                              const float& y);
    void serialize_pos_into(std::vector<uint8_t>& out, const Position& pos);
    void serialize_dir_into(std::vector<uint8_t>& out, const Direction& dir);
    void serialize_string_into(std::vector<uint8_t>& out, const std::string& str);

    // deserialization

    float deserialize_float_from(std::vector<uint8_t>::iterator& in);
    Position deserialize_pos_from(std::vector<uint8_t>::iterator& in);
    Direction deserialize_dir_from(std::vector<uint8_t>::iterator& in);
    std::string deserialize_string_from(std::vector<uint8_t>::iterator& in);
};

#endif
