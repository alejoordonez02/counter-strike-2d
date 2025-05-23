#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "../../common/position.h"

/*
 * la trayectoria podría ser un atributo de Weapon, de esa forma
 * se podría sobrecargar intersects según, por ejemplo, la accuracy
 * de la misma
 * */
class Trajectory {
private:
    Position origin;
    int angle;

public:
    Trajectory(const Position& origin, const int& angle): origin(origin), angle(angle) {}
    bool intersects(const Position& pos);
};

#endif
