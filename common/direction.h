#ifndef DIRECTION_H
#define DIRECTION_H

#include <cmath>

#include "tuple.h"

/*
 * Las direcciones son vectores unitarios (length = 1)
 * */
struct Direction: public Tuple<Direction, float> {
    Direction(const float& x, const float& y): Tuple<Direction, float>(0, 0) {
        float length = std::sqrt(x * x + y * y);
        if (length != 0) {
            this->x = x / length;
            this->y = y / length;
        }
    }
};

#endif
