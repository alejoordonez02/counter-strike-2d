#ifndef SERVER_GAME_WORLD_ACTIONS_RELOAD_H
#define SERVER_GAME_WORLD_ACTIONS_RELOAD_H

#include "action_strategy.h"
#include "equipment/weapon.h"

class Reload: public ActionStrategy {
private:
    std::shared_ptr<Weapon> weapon;
    Timer reload_time;

public:
    Reload(std::shared_ptr<Weapon> weapon);

    void update(float dt) override;
};

#endif
