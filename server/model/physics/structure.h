#ifndef SERVER_MODEL_STRUCTURE_H
#define SERVER_MODEL_STRUCTURE_H

#include <optional>

#include "common/position.h"
#include "server/model/hitbox.h"

class Structure: public Hitbox {
private:
    float length;  // longitud de los lados

public:
    Structure(Position center, float length): Hitbox(center), length(length) {}

    /*
     * Calcula la proyección del inner closest de Trajectory sobre el perímetro
     * del rectángulo, si la distancia del outter closest al centro del cuadrado
     * es menor a la primera distancia, entonces hay colisión
     * */
    std::optional<Position> intersect(const Trajectory& t) const override {
        auto closest = t.get_outter_and_inner_closest(pos);
        float center_to_closest = pos.get_distance(closest.first);
        Direction to_inner_closest = pos.get_direction(closest.second);
        float center_to_perimeter =
            (length / 2) / std::max(std::abs(to_inner_closest.x),
                                    std::abs(to_inner_closest.y));
        if (center_to_closest > center_to_perimeter) return std::nullopt;
        Position intersection =
            pos + pos.get_direction(closest.second) * center_to_perimeter;
        return intersection;
    }

    /*
     * No hace nada
     * */
    void get_attacked(int /* damage */) override {}
};

#endif
