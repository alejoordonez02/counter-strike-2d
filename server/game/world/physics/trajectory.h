#ifndef SERVER_WORLD_PHYSICS_TRAJECTORY_H
#define SERVER_WORLD_PHYSICS_TRAJECTORY_H

#include "common/position.h"

class Trajectory {
private:
    const float width;
    const Position origin;
    const Position destine;
    const Direction direction;
    const float length;

    Position eval(const float& t) const;

public:
    Trajectory(const Position& origin, const Position& destine,
               float width = 0);

    std::pair<Position, Position> get_outter_and_inner_closest(
        const Position& pos) const;
};

#endif
