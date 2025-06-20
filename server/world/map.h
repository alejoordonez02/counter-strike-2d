#ifndef SERVER_MODEL_MAP_H
#define SERVER_MODEL_MAP_H

#include <memory>
#include <vector>

#include "server/world/equipment/bomb.h"
#include "server/world/physics/hitbox.h"

class Map {
private:
    /*
     * Comparte los ptrs con Game y con los PlayerHandler
     * */
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::unique_ptr<Bomb> bomb;
    Position bomb_site;

public:
    Map();

    void update(float dt);

    void restart();

    Position get_tt_spawn() const;

    Position get_ct_spawn() const;

    void add_collidable(std::shared_ptr<Hitbox> cll);

    std::vector<std::shared_ptr<Hitbox>>& get_collidables();

    void plant_bomb(std::unique_ptr<Bomb> bomb, const Position& pos);

    bool bomb_has_exploded() const;

    bool bomb_is_planted() const;

    bool bomb_is_defused() const;
};

#endif
