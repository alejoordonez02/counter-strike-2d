#ifndef SERVER_CMD_CONSTRUCTOR_H
#define SERVER_CMD_CONSTRUCTOR_H

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "aim.h"
#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "player_command.h"
#include "start_attacking.h"
#include "start_moving.h"
#include "start_planting.h"
#include "stop_attacking.h"
#include "stop_moving.h"
#include "stop_planting.h"

using namespace DTOSerial::PlayerCommands;

using CmdMaker =
    std::function<std::unique_ptr<Command>(std::unique_ptr<DTO>&&)>;

class CmdConstructor {
private:
    std::unordered_map<uint8_t, CmdMaker> maker_map;

public:
    CmdConstructor() {
        maker_map = {
            {AIM,
             [](auto&& dto_p) {
                 return std::make_unique<Aim>(std::move(dto_p));
             }},
            {START_MOVING,
             [](auto&& dto_p) {
                 return std::make_unique<StartMoving>(std::move(dto_p));
             }},
            {STOP_MOVING,
             [](auto&& /* dto_p */) { return std::make_unique<StopMoving>(); }},
            {START_ATTACKING,
             [](auto&& dto_p) {
                 return std::make_unique<StartAttacking>(std::move(dto_p));
             }},
            {STOP_ATTACKING,
             [](auto&& /* dto_p */) {
                 return std::make_unique<StopAttacking>();
             }},
            {START_PLANTING,
             [](auto&& dto_p) {
                 return std::make_unique<StartPlanting>(std::move(dto_p));
             }},
            {STOP_PLANTING,
             [](auto&& /* dto_p */) {
                 return std::make_unique<StopPlanting>();
             }},
        };
    }

    std::unique_ptr<Command> construct(std::unique_ptr<DTO>&& dto_p) {
        uint8_t cmd_type = dto_p->get_type();

        if (not maker_map.count(cmd_type))
            throw std::runtime_error(
                "CmdConstructor error: unknown Command type");

        CmdMaker f = maker_map.at(cmd_type);

        return f(std::move(dto_p));
    }

    CmdConstructor(const CmdConstructor&) = delete;
    CmdConstructor& operator=(const CmdConstructor&) = delete;

    CmdConstructor(CmdConstructor&&) = default;
    CmdConstructor& operator=(CmdConstructor&&) = default;

    ~CmdConstructor() = default;
};

#endif
