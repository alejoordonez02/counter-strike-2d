#include "server/world/physics/structure.h"

#include <optional>

#include "common/position.h"
#include "server/world/physics/hitbox.h"

Structure::Structure(Position center, float length):
    Hitbox(center), length(length) {}

std::optional<Position> Structure::intersect(const Trajectory& t) const {
    auto closest = t.get_outter_and_inner_closest(pos);
    float center_to_closest = pos.get_distance(closest.first);
    Direction to_inner_closest = pos.get_direction(closest.second);
    float center_to_perimeter =
        (length / 2) /
        std::max(std::abs(to_inner_closest.x), std::abs(to_inner_closest.y));
    if (center_to_closest > center_to_perimeter) return std::nullopt;
    Position intersection =
        pos + pos.get_direction(closest.second) * center_to_perimeter;
    return intersection;
}

void Structure::get_attacked(int /* damage */) {}
