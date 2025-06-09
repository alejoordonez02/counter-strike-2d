#ifndef START_MOVING_DTO_H
#define START_MOVING_DTO_H

#include <cstdint>
#include <vector>

#include "../../direction.h"
#include "../dto.h"
#include "../protocol.h"

class StartMovingDTO: public DTO {
private:
    Direction dir;

    friend class StartMoving;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        dir = deserialize_dir(i);
    }

public:
    explicit StartMovingDTO(std::vector<uint8_t>&& bytes): DTO(std::move(bytes)) {
        deserialize();
    }

    explicit StartMovingDTO(const Direction& d): DTO(DTOSerial::PlayerCommands::MOVE), dir(d) {}

    void serialize_into(std::vector<uint8_t>& out) override {
        out.push_back(type);
        serialize_dir_into(out, dir);
    }

    ~StartMovingDTO() = default;

    /* BORRAR ESTO -alepaff*/
    Direction get_direction(){
        return dir;
    }
};

#endif
