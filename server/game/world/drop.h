#ifndef SERVER_GAME_WORLD_DROP_H
#define SERVER_GAME_WORLD_DROP_H

#include "common/position.h"
#include "equipment/weapon.h"
#include "snapshot_dto.h"
// #include "player.h"

class Player;

class Drop {
private:
    std::shared_ptr<Weapon> weapon;
    Position pos;

public:
    Drop(std::shared_ptr<Weapon> weapon, Position pos):
        weapon(std::move(weapon)), pos(pos) {}

    void push_drop_data(std::vector<WeaponDTO>& snapshot) {
        snapshot.push_back(WeaponDTO(weapon->get_name(), pos));
    }
};

#endif
