#include "map.h"

#include <memory>
#include <vector>

#include "equipment/bomb.h"
#include "physics/hitbox.h"
#include "physics/structure.h"

// TODO: make this configurable
#define BOMB_TIME 300

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
std::vector<Structure>& Map::get_bomb_site() { return bomb_site; }

void Map::plant_bomb(const Position& pos) {
    bomb = Bomb(pos, BOMB_TIME);
    bomb->plant();
}
