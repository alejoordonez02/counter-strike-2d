#ifndef SERVER_WORLD_ACTIONS_ATTACK_H
#define SERVER_WORLD_ACTIONS_ATTACK_H

#include "common/direction.h"
#include "server/world/actions/action_strategy.h"
#include "server/world/equipment/weapon.h"

class Player;

/*
 * Attack action strategy
 * */
class Attack: public ActionStrategy {
private:
    Position& pos;
    Direction& dir;
    Weapon& weapon;
    std::vector<std::shared_ptr<Hitbox>>& collidables;
    std::vector<size_t>& sorted_idx;

public:
    Attack(Position& pos, Direction& dir, Weapon& weapon,
           std::vector<std::shared_ptr<Hitbox>>& collidables,
           std::vector<size_t>& sorted_idx);

    void update(float dt) override;
};

#endif
