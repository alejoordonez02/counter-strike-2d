#ifndef SERVER_WORLD_ACTIONS_ATTACK_H
#define SERVER_WORLD_ACTIONS_ATTACK_H

#include "action_strategy.h"
#include "common/direction.h"
#include "server/game/world/equipment/weapon.h"

class Player;

/*
 * Attack action strategy
 * */
class Attack: public ActionStrategy {
private:
    Position& pos;
    Direction& dir;
    std::shared_ptr<Weapon> weapon;
    std::vector<std::shared_ptr<Hitbox>>& collidables;
    std::vector<size_t>& sorted_idx;
    int& kills;
    int& money;

public:
    Attack(Position& pos, Direction& dir, std::shared_ptr<Weapon> weapon,
           std::vector<std::shared_ptr<Hitbox>>& collidables,
           std::vector<size_t>& sorted_idx, int& kills, int& money);

    void update(float dt) override;

    bool is_attacking() const override { return true; }
};

#endif
