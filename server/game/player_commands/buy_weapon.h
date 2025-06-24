#ifndef SERVER_GAME_PLAYER_COMMANDS_BUY_WEAPON_H
#define SERVER_GAME_PLAYER_COMMANDS_BUY_WEAPON_H

#include <memory>

#include "common/network/dtos/buy_weapon_dto.h"
#include "player.h"
#include "player_command.h"

class BuyWeapon: public Command {
private:
    WeaponName name;

public:
    explicit BuyWeapon(const WeaponName& name): name(name) {}

    explicit BuyWeapon(std::unique_ptr<DTO>&& dto_p) {
        if (BuyWeaponDTO* buy_weapon_dto =
                dynamic_cast<BuyWeaponDTO*>(dto_p.get())) {
            name = std::move(buy_weapon_dto->weapon_name);
        } else {
            throw std::runtime_error("DTO is not of name BuyWeaponDTO");
        }
    }

    void execute(Player& p) const override { p.buy_weapon(name); }

    ~BuyWeapon() = default;
};

#endif
