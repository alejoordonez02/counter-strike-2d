#ifndef SERVER_WORLD_PHYSICS_STRUCTURE_H
#define SERVER_WORLD_PHYSICS_STRUCTURE_H

#include <optional>

#include "common/position.h"
#include "hitbox.h"

class Structure: public Hitbox {
private:
    float length;

    float get_distance_to_perimeter(const Direction& dir) const;

public:
    Structure(Position center, float length);

    /*
     * Calcula la proyección del inner closest de Trajectory sobre el
     * perímetro del rectángulo, si la distancia del outter closest al
     * centro del cuadrado es menor a la primera distancia, entonces hay
     * colisión
     * */
    std::optional<Position> intersect(const Trajectory& t) const override;

    bool intersects(const Position& pos) const;

    /*
     * No hace nada
     * */
    void get_attacked(int /* damage */) override;
};

#endif
