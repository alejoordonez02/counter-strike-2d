#ifndef ATTACK_H
#define ATTACK_H

#include "common/direction.h"

#include "action_strategy.h"
#include "map.h"
#include "player_physics.h"
#include "weapon.h"

/*
 * Attack
 * */
class Attack: public ActionStrategy {
private:
    const PlayerPhysics& physics;
    const Position& pos;
    const Direction& dir;
    Weapon& weapon;
    Map& map;

public:
    Attack(PlayerPhysics& physics, Position& pos, Direction& dir, Weapon& weapon, Map& map);
    void update(float dt) override;
};

#endif
