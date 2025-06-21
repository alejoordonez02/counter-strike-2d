#ifndef SERVER_MODEL_MAP_H
#define SERVER_MODEL_MAP_H

#include <memory>
#include <vector>

#include "server/world/equipment/bomb.h"
#include "server/world/physics/hitbox.h"
#include "server/world/physics/structure.h"

class Map {
private:
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::vector<Structure> bomb_site;
    std::vector<Position> tt_spawn;
    std::vector<Position> ct_spawn;
    std::optional<Bomb> bomb;

public:
    Map(const std::vector<std::shared_ptr<Hitbox>>& collidables,
        const std::vector<Structure>& bomb_site,
        const std::vector<Position>& tt_spawn,
        const std::vector<Position>& ct_spawn);

    void update(float dt);

    void restart();

    Position get_tt_spawn() const;

    Position get_ct_spawn() const;

    void add_collidable(std::shared_ptr<Hitbox> cll);

    std::vector<std::shared_ptr<Hitbox>>& get_collidables();

    void plant_bomb(std::optional<Bomb> bomb, const Position& pos);

    bool bomb_has_exploded() const;

    bool bomb_is_planted() const;

    bool bomb_is_defused() const;
};

#endif
