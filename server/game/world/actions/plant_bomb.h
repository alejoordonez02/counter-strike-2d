#ifndef SERVER_GAME_WORLD_ACTIONS_PLANT_BOMB_H
#define SERVER_GAME_WORLD_ACTIONS_PLANT_BOMB_H

#include <memory>

#include "action_strategy.h"
#include "map.h"
#include "server/game/world/timer.h"

class PlantBomb: public ActionStrategy {
private:
    /*
     * si ésto va a estar en config entonces tiene que ser
     * un atributo de player para que lo pase a la hora de
     * instanciar ésta action
     * */
    bool& has_bomb;
    Position pos;
    std::weak_ptr<Map>& map;
    Timer time_to_plant;

public:
    PlantBomb(bool& has_bomb, Position pos, std::weak_ptr<Map>& map,
              int time_to_plant);

    void update(float dt);
};

#endif
