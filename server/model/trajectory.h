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
    float m;  // pendiente
    float b;  // desplazamiento

    float eval(const float& x) const { return m * x + b; }

public:
    Trajectory(const Position& origin, const Position& destination):
            m((destination.y - origin.y) / (destination.x - origin.x)),
            b(origin.y - m * origin.x) {}

    bool intersects(const Position& pos) const {
        /*
         * Por ahora no estoy considerando ningún tipo de hitbox,
         * pero intersects pordría recibir un float hitbox que sea
         * el tamaño del rango a checkear para intersecar (>,<)
         * */
        if (pos.y == eval(pos.x))
            return true;
        return false;
    }
};

#endif
