#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>

#include "hitbox.h"

/*
 * El mapa contiene tanto los objetos estáticos, como los dinámicos.
 * Existen objetos colisionables, y en particular, todos los dinámicos
 * son colisionables y viceversa, así que los llamamos con un sólo
 * nombre: collidables
 * */
class Map {
private:
    std::vector<std::unique_ptr<Hitbox>> collidables;

public:
    Map(): collidables() {}

    void add_collidable(std::unique_ptr<Hitbox>&& cll) { collidables.push_back(std::move(cll)); }

    std::vector<std::unique_ptr<Hitbox>>& get_collidable() { return collidables; }
};

#endif
