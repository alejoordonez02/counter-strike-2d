#ifndef DTO_CONSTRUCTOR_H
#define DTO_CONSTRUCTOR_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <cstdint>

#include "dto.h"
#include "protocol.h"
#include "dtos/move_dto.h"
#include "dtos/attack_dto.h"

using namespace DTOSerial::PlayerCommands;
// using namespace DTOSerial:: otros;

using DTOMaker = std::function<std::unique_ptr<DTO>(std::vector<uint8_t>&&)>;


class DTOConstructor {
private:
    std::unordered_map<uint8_t, DTOMaker> maker_map;

public:
    DTOConstructor() {
        maker_map = {
            {MOVE, [](auto&& bytes) { return std::make_unique<MoveDTO>(bytes); }},
            {ATTACK, [](auto&& bytes) { return std::make_unique<AttackDTO>(bytes); }},
            // ...
        };
    }

    std::unique_ptr<DTO> construct(std::vector<uint8_t>&& bytes) {
        if (not maker_map.count(bytes[0]))
            throw std::runtime_error("DTOConstructor error: unknown DTO type");

        DTOMaker f = maker_map.at(bytes[0]);
        
        return f(std::move(bytes));
    }

    DTOConstructor(const DTOConstructor&) = delete;
    DTOConstructor& operator=(const DTOConstructor&) = delete;

    DTOConstructor(DTOConstructor&&) = default;
    DTOConstructor& operator=(DTOConstructor&&) = default;

    ~DTOConstructor() = default;
};

#endif
