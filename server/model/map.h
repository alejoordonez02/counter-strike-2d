#ifndef SERVER_MODEL_MAP_H
#define SERVER_MODEL_MAP_H

#include <functional>
#include <memory>
#include <vector>

#include "server/model/bomb.h"
#include "server/model/hitbox.h"

#define BOMB_SITE_RADIUS 10

/*
 * El mapa contiene tanto los objetos estáticos, como los dinámicos.
 * Existen objetos colisionables, y en particular, todos los dinámicos
 * son colisionables y viceversa, así que los llamamos con un sólo
 * nombre: collidables
 * */
class Map {
private:
    /*
     * Comparte los ptrs con Game y con los PlayerHandler
     * */
    std::vector<std::shared_ptr<Hitbox>> collidables;
    std::unique_ptr<Bomb> bomb;
    Position bomb_site;

public:
    Map(): collidables(0), bomb() {}

    /*
     * Update
     * */
    void update(float dt) {
        if (bomb)
            bomb->update(dt);
    }

    /*
     * Restart
     * */
    void restart() { bomb = nullptr; }

    /*
     * Sites
     * */
    Position get_tt_spawn() const;

    Position get_ct_spawn() const;

    /*
     * Collidables
     * */
    void add_collidable(std::shared_ptr<Hitbox> cll) {
        collidables.push_back(cll);
    }

    std::vector<std::shared_ptr<Hitbox>>& get_collidables() {
        return collidables;
    }

    /*
     * Bomb
     * */
    void plant_bomb(std::unique_ptr<Bomb> bomb, const Position& pos) {
        if (bomb_site.get_distance(pos) < BOMB_SITE_RADIUS) {
            this->bomb = std::move(bomb);
            bomb->plant();
        }
    }

    bool bomb_has_exploded() const {
        if (!bomb)
            return false;
        return bomb->has_exploded();
    }

    bool bomb_is_planted() const {
        if (!bomb)
            return false;
        return bomb->is_defused();
    }

    bool bomb_is_defused() const {
        if (!bomb)
            return false;
        return bomb->is_defused();
    }
};

#endif
