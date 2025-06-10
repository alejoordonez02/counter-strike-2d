#ifndef DTO_H
#define DTO_H

#include "../position.h"
#include "../direction.h"

#include <cstdint>
#include <vector>
#include <bit>
#include <arpa/inet.h>
#include <cstring>
#include <string>

class DTO {
protected:
    uint8_t type;
    std::vector<uint8_t> payload;
    bool _is_serialized;

    explicit DTO(std::vector<uint8_t>&& bytes): type(bytes[0]), payload(std::move(bytes)), _is_serialized(true) {}
    explicit DTO(const uint8_t type): type(type), _is_serialized(false) {}

    virtual void deserialize() = 0;

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
    void serialize_tuple_into(std::vector<uint8_t>& out, const float& x, const float& y);
    void serialize_pos_into(std::vector<uint8_t>& out, const Position& pos);
    void serialize_dir_into(std::vector<uint8_t>& out, const Direction& dir);
    void serialize_string_into(std::vector<uint8_t>& out, const std::string& str);

    // deserialization

    float deserialize_float(int& i);
    Position deserialize_pos(int& i);
    Direction deserialize_dir(int& i);
    std::string deserialize_string(int& i);
};

#endif
