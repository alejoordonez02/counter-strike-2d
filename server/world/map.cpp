#include "server/world/map.h"

#include <memory>
#include <vector>

#include "server/world/equipment/bomb.h"
#include "server/world/physics/hitbox.h"

#define BOMB_SITE_RADIUS 10

Map::Map(): collidables(0), bomb() {}

/*
 * Update
 * */
void Map::update(float dt) {
    if (bomb) bomb->update(dt);
}

/*
 * Restart
 * */
void Map::restart() { bomb = nullptr; }

/*
 * Sites
 * */
// Position Map::get_tt_spawn() const {}
// Position Map::get_ct_spawn() const {}

/*
 * Collidables
 * */
void Map::add_collidable(std::shared_ptr<Hitbox> cll) {
    collidables.push_back(cll);
}

std::vector<std::shared_ptr<Hitbox>>& Map::get_collidables() {
    return collidables;
}

/*
 * Bomb
 * */
void Map::plant_bomb(std::unique_ptr<Bomb> bomb, const Position& pos) {
    if (bomb_site.get_distance(pos) < BOMB_SITE_RADIUS) {
        this->bomb = std::move(bomb);
        bomb->plant();
    }
}

bool Map::bomb_has_exploded() const {
    if (!bomb) return false;
    return bomb->has_exploded();
}

bool Map::bomb_is_planted() const {
    if (!bomb) return false;
    return bomb->is_defused();
}

bool Map::bomb_is_defused() const {
    if (!bomb) return false;
    return bomb->is_defused();
}
