#ifndef SERVER_GAME_PLAYER_COMMANDS_BUY_AMMO_H
#define SERVER_GAME_PLAYER_COMMANDS_BUY_AMMO_H

#include <memory>

#include "common/network/dtos/buy_ammo_dto.h"
#include "player.h"
#include "player_command.h"

class BuyAmmo: public Command {
private:
    WeaponType type;
    int count;

public:
    explicit BuyAmmo(const WeaponType& type, const int& count):
        type(type), count(count) {}

    explicit BuyAmmo(std::unique_ptr<DTO>&& dto_p) {
        if (BuyAmmoDTO* buy_ammo_dto = dynamic_cast<BuyAmmoDTO*>(dto_p.get())) {
            type = std::move(buy_ammo_dto->weapon_type);
            count = std::move(buy_ammo_dto->count);
        } else {
            throw std::runtime_error("DTO is not of type BuyAmmoDTO");
        }
    }

    void execute(Player& p) const override { p.buy_ammo(type, count); }

    ~BuyAmmo() = default;
};

#endif
