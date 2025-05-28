#ifndef POSITION_H
#define POSITION_H

#include "direction.h"
#include "tuple.h"

struct Position: public Tuple<Position, float> {
    Position(const float& x, const float& y): Tuple(x, y) {}

    float get_distance(const Position& pos) const { return (*this - pos).get_length(); }

    float dot(const Direction& dir) const { return x * dir.x + y * dir.y; }

    Position& operator+=(const Direction& dir) {
        x += dir.x;
        y += dir.y;
        return *this;
    }
};

#endif
