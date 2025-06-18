#ifndef COMMON_POSITION_H
#define COMMON_POSITION_H

#include "common/direction.h"
#include "common/tuple.h"

struct Position: public Tuple<Position, float> {
    Position(): Tuple(0, 0) {}

    Position(const float& x, const float& y): Tuple(x, y) {}

    float get_distance(const Position& pos) const {
        return (*this - pos).get_length();
    }

    float dot(const Direction& dir) const { return x * dir.x + y * dir.y; }

    Direction get_direction(const Position& to) const {
        return Direction(to.x - x, to.y - y);
    }

    Position operator+(const Position& pos) const {
        return Position(x + pos.x, y + pos.y);
    }

    Position operator+(const Direction& dir) const {
        return Position(x + dir.x, y + dir.y);
    }

    Position operator-(const Position& pos) const {
        return Position(x - pos.x, y - pos.y);
    }

    Position operator-(const Direction& dir) const {
        return Position(x - dir.x, y - dir.y);
    }

    Position& operator+=(const Position& pos) {
        x += pos.x;
        y += pos.y;
        return *this;
    }

    Position& operator+=(const Direction& dir) {
        x += dir.x;
        y += dir.y;
        return *this;
    }
};

#endif
