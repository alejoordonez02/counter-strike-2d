#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>

#include "collidable.h"

/*
 * El mapa contiene tanto los objetos estáticos, como los dinámicos.
 * Existen objetos colisionables, y en particular, todos los dinámicos
 * son colisionables y viceversa, así que los llamamos con un sólo
 * nombre: collidable
 * */
class Map {
private:
    std::vector<std::unique_ptr<Collidable>> collidable;

public:
    Map(): collidable() {}
    void add_collidable(std::unique_ptr<Collidable>&& cll) { collidable.push_back(std::move(cll)); }
    std::vector<std::unique_ptr<Collidable>>& get_collidable() { return collidable; }
};

#endif
