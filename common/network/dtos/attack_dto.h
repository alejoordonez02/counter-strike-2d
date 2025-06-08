#ifndef ATTACK_DTO_H
#define ATTACK_DTO_H

#include <cstdint>
#include <vector>

#include "../../position.h"
#include "../dto.h"
#include "../protocol.h"

class AttackDTO: public DTO {
private:
    Position pos;

    friend class StartAttacking;

    void deserialize() override {
        int i = 1;  // skip 1st byte (DTO type)
        pos = deserialize_pos(i);
    }

public:
    explicit AttackDTO(std::vector<uint8_t>&& bytes) {
        payload = std::move(bytes);
        deserialize();
    }

    explicit AttackDTO(const Position& p): DTO(DTOSerial::PlayerCommands::ATTACK), pos(p) {}

    const std::vector<uint8_t>& serialize() override {
        if (_is_serialized)
            return payload;

        serialize_pos(pos);
        _is_serialized = true;

        return payload;
    }

    ~AttackDTO() = default;
};

#endif
