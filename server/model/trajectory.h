#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "../../common/position.h"

/*
 * la trayectoria podría ser un atributo de Weapon, de esa forma
 * se podría sobrecargar intersects según, por ejemplo, la accuracy
 * de la misma
 * */
class Trajectory {
public:
    const Position origin;
    const Position destination;

    Trajectory(const Position& origin, const Position& destination):
            origin(origin), destination(destination) {}

    Position eval(const float& t) const { return origin + (destination - origin) * t; }

    float get_length() const { return origin.get_distance(destination); }

    Direction get_direction() const {
        auto dir = destination - origin;
        return Direction(dir.x, dir.y);
    }
};

#endif
