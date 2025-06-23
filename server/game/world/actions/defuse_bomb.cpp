#include "defuse_bomb.h"

#include <memory>

#include "map.h"
#include "position.h"

DefuseBomb::DefuseBomb(Position pos, std::weak_ptr<Map>& map,
                       int time_to_defuse):
    pos(pos), map(map), time_to_defuse(time_to_defuse) {}

void DefuseBomb::update(float dt) {
    time_to_defuse.update(dt);
    if (!time_to_defuse.is_done()) return;
    map.lock()->defuse_bomb();
}
