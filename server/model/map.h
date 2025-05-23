#ifndef MAP_H
#define MAP_H

#include <vector>

#include "collidable.h"

/*
 * El mapa contiene tanto los objetos estáticos, como los dinámicos.
 * Existen objetos colisionables, y en particular, todos los dinámicos
 * son colisionables y viceversa, así que los llamamos con un sólo
 * nombre: collidable
 * */
class Map {
public:
    std::vector<Collidable> get_collidable();
};

#endif
