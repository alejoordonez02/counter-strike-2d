#include "plant_bomb.h"

#include <memory>

#include "map.h"
#include "server/game/world/timer.h"

PlantBomb::PlantBomb(bool& has_bomb, Position pos, std::weak_ptr<Map>& map,
                     int time_to_plant):
    has_bomb(has_bomb), pos(pos), map(map), time_to_plant(time_to_plant) {}

void PlantBomb::update(float dt) {
    time_to_plant.update(dt);
    if (!time_to_plant.is_done()) return;
    map.lock()->plant_bomb(pos);
    has_bomb = false;
}
