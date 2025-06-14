#ifndef SERVER_MODEL_ATTACK_H
#define SERVER_MODEL_ATTACK_H

#include "common/direction.h"
#include "server/model/action_strategy.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"
#include "server/model/weapon.h"

/*
 * Attack
 * */
class Attack: public ActionStrategy {
private:
    const PlayerPhysics& physics;
    const Position& pos;
    const Direction& dir;
    Weapon& weapon;
    std::weak_ptr<Map> map;

public:
    Attack(PlayerPhysics& physics, Position& pos, Direction& dir,
           Weapon& weapon, std::weak_ptr<Map> map);
    void update(float dt) override;
};

#endif
