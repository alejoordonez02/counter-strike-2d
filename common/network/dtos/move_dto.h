#ifndef MOVE_DTO_H
#define MOVE_DTO_H

#include <cstdint>
#include <vector>

#include "../../direction.h"
#include "../dto.h"
#include "../protocol.h"

class MoveDTO: public DTO {
private:
    Direction dir;

    friend class StartMoving;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        dir = deserialize_dir(i);
    }

public:
    explicit MoveDTO(std::vector<uint8_t>&& bytes) {
        payload = std::move(bytes);
        deserialize();
    }

    explicit MoveDTO(const Direction& d): DTO(DTOSerial::PlayerCommands::MOVE), dir(d) {}

    const std::vector<uint8_t>& serialize() override {
        if (_is_serialized)
            return payload;

        serialize_dir(dir);
        _is_serialized = true;

        return payload;
    }

    ~MoveDTO() = default;
};

#endif
