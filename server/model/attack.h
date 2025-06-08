#ifndef ATTACK_H
#define ATTACK_H

#include "common/direction.h"

#include "action_strategy.h"
#include "weapon.h"

/*
 * Attack
 * */
class Attack: public ActionStrategy {
private:
    Direction& dir;
    Weapon& weapon;

public:
    Attack(Direction& dir, Weapon& weapon);
    void update(float dt) override;
};

#endif
