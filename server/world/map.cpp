#include "server/world/map.h"

#include <memory>
#include <vector>

#include "server/world/equipment/bomb.h"
#include "server/world/physics/hitbox.h"

#define BOMB_SITE_RADIUS 10

Map::Map(const std::vector<std::shared_ptr<Hitbox>>& collidables,
         const std::vector<Structure>& bomb_site,
         const std::vector<Position>& tt_spawn,
         const std::vector<Position>& ct_spawn):
    collidables(collidables), bomb_site(bomb_site), tt_spawn(tt_spawn),
    ct_spawn(ct_spawn), bomb(std::nullopt) {}

/*
 * Update
 * */
void Map::update(float dt) {
    if (bomb) bomb->update(dt);
}

/*
 * Restart
 * */
void Map::restart() { bomb = std::nullopt; }

/*
 * Sites TODO: WIP
 * */
Position Map::get_tt_spawn() const { return tt_spawn[0]; }
Position Map::get_ct_spawn() const { return ct_spawn[0]; }

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
void Map::plant_bomb(std::optional<Bomb> bomb, const Position& pos) {
    /* if (bomb_site.get_distance(pos) < BOMB_SITE_RADIUS) {
        this->bomb = bomb;
        bomb->plant();
    } */
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
