#ifndef SERVER_MODEL_TRAJECTORY_H
#define SERVER_MODEL_TRAJECTORY_H

#include <algorithm>

#include "common/position.h"

class Trajectory {
private:
    const float width;
    const Position origin;
    const Position destine;
    const Direction direction;
    const float length;

public:
    Trajectory(const Position& origin, const Position& destine,
               float width = 0):
        width(width), origin(origin), destine(destine),
        direction(origin.get_direction(destine)),
        length(origin.get_distance(destine)) {}

    Position eval(const float& t) const {
        return origin + (destine - origin) * t;
    }

    Position get_closest(const Position& pos) const {
        float t = std::clamp((pos - origin).dot(direction) / length, 0.f, 1.f);
        auto inner = eval(t);
        auto dir = inner.get_direction(pos);
        return inner + dir * width;
    }

    float get_length() const { return length; }
};

#endif
