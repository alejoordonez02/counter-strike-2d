#ifndef POSITION_H
#define POSITION_H

#include "direction.h"
#include "tuple.h"

struct Position: public Tuple<float> {
    Position(const float& x, const float& y): Tuple(x, y) {}

    Position& operator+=(const Direction& dir) {
        x += dir.x;
        y += dir.y;
        return *this;
    }
};

#endif
