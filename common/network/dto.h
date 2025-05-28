#ifndef DTO_H
#define DTO_H

#include <cstdint>
#include <vector>
#include <iterator>
#include <bit>
#include <arpa/inet.h>
#include <cstring>

class DTO {
protected:
    const uint8_t type;
    std::vector<uint8_t> data;

    DTO(const uint8_t t): type(t) {}

    std::vector<uint8_t> serialize_float(const float& n) {
        auto srlzd_n = std::bit_cast<uint32_t>(n);
        srlzd_n = htonl(srlzd_n);
        std::vector<uint8_t> bytes(sizeof(srlzd_n));
        std::memcpy(bytes.data(), &srlzd_n, sizeof(srlzd_n));
        return bytes;
    }

public:
    DTO(const std::vector<uint8_t>&& bytes): 
            type(bytes[0]), 
            data(std::make_move_iterator(bytes.begin() + 1),
                 std::make_move_iterator(bytes.end())) {}


    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buf;

        buf.push_back(type);
        buf.insert(buf.end(), data.begin(), data.end());

        return buf;
    }

    uint8_t get_type() const { return type; }

    const std::vector<uint8_t>& get_data() const { return data; }


    DTO(const DTO&) = delete;
    DTO& operator=(const DTO&) = delete;

    DTO(DTO&&) = default;
    DTO& operator=(DTO&&) = default;

    virtual ~DTO() = default;
};

#endif
