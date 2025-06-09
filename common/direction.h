#ifndef COMMON_DIRECTION_H
#define COMMON_DIRECTION_H

#include <cmath>

#include "common/tuple.h"

/*
 * Las direcciones son vectores unitarios (length = 1)
 * */
struct Direction: public Tuple<Direction, float> {
    Direction(): Tuple<Direction, float>(0, 0) {}

    Direction(const float& x, const float& y, bool normalized = true):
            Tuple<Direction, float>(0, 0) {
        if (normalized) {
            float length = std::sqrt(x * x + y * y);
            if (length != 0) {
                this->x = x / length;
                this->y = y / length;
            }
        } else {
            this->x = x;
            this->y = y;
        }
    }

    Direction operator*(const float& n) const {
        return Direction(x * n, y * n, false);
    }
};

#endif
