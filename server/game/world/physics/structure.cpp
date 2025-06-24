#include "structure.h"

#include <optional>

#include "common/position.h"
#include "hitbox.h"

Structure::Structure(Position center, float length):
    Hitbox(center), length(length) {}

float Structure::get_distance_to_perimeter(const Direction& dir) const {
    return (length / 2) / std::max(std::abs(dir.x), std::abs(dir.y));
}

std::optional<Position> Structure::intersect(const Trajectory& t) const {
    auto closest = t.get_outter_and_inner_closest(pos);
    float center_to_closest = pos.get_distance(closest.first);
    Direction to_inner_closest = pos.get_direction(closest.second);
    float center_to_perimeter = get_distance_to_perimeter(to_inner_closest);
    if (center_to_closest > center_to_perimeter) return std::nullopt;
    Position intersection =
        pos + pos.get_direction(closest.second) * center_to_perimeter;
    return intersection;
}

bool Structure::intersects(const Position& pos) const {
    Direction to_pos = this->pos.get_direction(pos);
    float distance = this->pos.get_distance(pos);
    float distance_to_perimeter = get_distance_to_perimeter(to_pos);
    return distance < distance_to_perimeter;
}

void Structure::get_attacked(int /* damage */) {}
