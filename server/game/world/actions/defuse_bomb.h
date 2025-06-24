#ifndef SERVER_GAME_WORLD_ACTIONS_DEFUSE_BOMB_H
#define SERVER_GAME_WORLD_ACTIONS_DEFUSE_BOMB_H

#include <memory>

#include "action_strategy.h"
#include "map.h"
#include "position.h"

class DefuseBomb: public ActionStrategy {
private:
    Position pos;
    std::weak_ptr<Map>& map;
    Timer time_to_defuse;

public:
    DefuseBomb(Position pos, std::weak_ptr<Map>& map, int time_to_defuse);

    void update(float dt) override;
};

#endif
