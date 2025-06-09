#ifndef SERVER_MODEL_MAP_H
#define SERVER_MODEL_MAP_H

#include <functional>
#include <vector>

#include "server/model/hitbox.h"

/*
 * El mapa contiene tanto los objetos estáticos, como los dinámicos.
 * Existen objetos colisionables, y en particular, todos los dinámicos
 * son colisionables y viceversa, así que los llamamos con un sólo
 * nombre: collidables
 * */
class Map {
    private:
    std::vector<std::reference_wrapper<Hitbox>> dynamic_collidables;

    public:
    Map(): dynamic_collidables() {}

    void add_collidable(Hitbox& cll) { dynamic_collidables.push_back(cll); }

    std::vector<std::reference_wrapper<Hitbox>>& get_collidable() {
        return dynamic_collidables;
    }
};

#endif
