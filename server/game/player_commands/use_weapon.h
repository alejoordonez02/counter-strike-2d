#ifndef SERVER_GAME_PLAYER_COMMANDS_USE_WEAPON_H
#define SERVER_GAME_PLAYER_COMMANDS_USE_WEAPON_H

#include <memory>

#include "player.h"
#include "player_command.h"
#include "use_weapon_dto.h"

class UseWeapon: public Command {
private:
    WeaponType type;

public:
    explicit UseWeapon(const WeaponType& type): type(type) {}

    explicit UseWeapon(std::unique_ptr<DTO>&& dto_p) {
        if (UseWeaponDTO* use_weapon_dto =
                dynamic_cast<UseWeaponDTO*>(dto_p.get())) {
            type = std::move(use_weapon_dto->weapon_type);
        } else {
            throw std::runtime_error("DTO is not of type UseWeaponDTO");
        }
    }

    void execute(Player& p) const override { p.use_weapon(type); }

    ~UseWeapon() = default;
};

#endif
