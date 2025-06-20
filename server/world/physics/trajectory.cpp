#include "server/world/physics/trajectory.h"

#include <algorithm>

#include "common/position.h"

Position Trajectory::eval(const float& t) const {
    return origin + (destine - origin) * t;
}

Trajectory::Trajectory(const Position& origin, const Position& destine,
                       float width):
    width(width), origin(origin), destine(destine),
    direction(origin.get_direction(destine)),
    length(origin.get_distance(destine)) {}

std::pair<Position, Position> Trajectory::get_outter_and_inner_closest(
    const Position& pos) const {
    if (!length)
        return std::make_pair(origin + origin.get_direction(pos) * width,
                              origin);

    float t = std::clamp((pos - origin).dot(direction) / length, 0.f, 1.f);
    auto inner = eval(t);
    auto dir = inner.get_direction(pos);
    return std::make_pair(inner + dir * width, inner);
}
