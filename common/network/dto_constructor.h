#ifndef COMMON_NETWORK_DTO_CONSTRUCTOR_H
#define COMMON_NETWORK_DTO_CONSTRUCTOR_H

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/network/dto.h"
#include "common/network/dtos/aim_dto.h"
#include "common/network/dtos/snapshot_dto.h"
#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "common/network/dtos/stop_moving_dto.h"
#include "common/network/protocol.h"
#include "stop_attacking_dto.h"

using namespace DTOSerial::PlayerCommands;
// using namespace DTOSerial:: otros;

using DTOMaker = std::function<std::unique_ptr<DTO>(std::vector<uint8_t>&&)>;

class DTOConstructor {
private:
    std::unordered_map<uint8_t, DTOMaker> maker_map;

public:
    DTOConstructor() {
        maker_map = {
            {AIM,
             [](auto&& bytes) {
                 return std::make_unique<AimDTO>(std::move(bytes));
             }},
            {START_MOVING,
             [](auto&& bytes) {
                 return std::make_unique<StartMovingDTO>(std::move(bytes));
             }},
            {STOP_MOVING,
             [](auto&& bytes) {
                 return std::make_unique<StopMovingDTO>(std::move(bytes));
             }},
            {START_ATTACKING,
             [](auto&& bytes) {
                 return std::make_unique<StartAttackingDTO>(std::move(bytes));
             }},
            {STOP_ATTACKING,
             [](auto&& bytes) {
                 return std::make_unique<StopAttackingDTO>(std::move(bytes));
             }},
            {SNAPSHOT,
             [](auto&& bytes) {
                 return std::make_unique<SnapshotDTO>(std::move(bytes));
             }},
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
