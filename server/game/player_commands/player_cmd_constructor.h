#ifndef SERVER_CMD_CONSTRUCTOR_H
#define SERVER_CMD_CONSTRUCTOR_H

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "aim.h"
#include "buy_ammo.h"
#include "buy_weapon.h"
#include "common/network/dto.h"
#include "common/network/protocol.h"
#include "drop.h"
#include "drop_bomb.h"
#include "pickup.h"
#include "player_command.h"
#include "start_attacking.h"
#include "start_defusing.h"
#include "start_moving.h"
#include "start_planting.h"
#include "start_reloading.h"
#include "stop_action.h"
#include "stop_moving.h"
#include "use_weapon.h"

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
            {USE_WEAPON,
             [](auto&& dto_p) {
                 return std::make_unique<UseWeapon>(std::move(dto_p));
             }},
            {BUY_WEAPON,
             [](auto&& dto_p) {
                 return std::make_unique<BuyWeapon>(std::move(dto_p));
             }},
            {BUY_AMMO,
             [](auto&& dto_p) {
                 return std::make_unique<BuyAmmo>(std::move(dto_p));
             }},
            {DROP_CURRENT,
             [](auto&& /* dto_p */) {
                 return std::make_unique<DropCurrent>();
             }},
            {DROP_BOMB,
             [](auto&& /* dto_p */) { return std::make_unique<DropBomb>(); }},
            {PICKUP,
             [](auto&& /* dto_p */) { return std::make_unique<Pickup>(); }},
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
            {START_PLANTING,
             [](auto&& dto_p) {
                 return std::make_unique<StartPlanting>(std::move(dto_p));
             }},
            {START_DEFUSING,
             [](auto&& dto_p) {
                 return std::make_unique<StartDefusing>(std::move(dto_p));
             }},
            {START_RELOADING,
             [](auto&& dto_p) {
                 return std::make_unique<StartReloading>(std::move(dto_p));
             }},
            {STOP_ACTION,
             [](auto&& /* dto_p */) { return std::make_unique<StopAction>(); }},
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
