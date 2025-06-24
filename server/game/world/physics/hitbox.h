#ifndef SERVER_WORLD_PHYSICS_HITBOX_H
#define SERVER_WORLD_PHYSICS_HITBOX_H

#include <optional>

#include "trajectory.h"

class Hitbox {
protected:
    Position pos;

public:
    explicit Hitbox(const Position& pos): pos(pos) {}

    virtual std::optional<Position> intersect(const Trajectory& t) const = 0;

    virtual bool get_attacked(int damage) = 0;

    Position get_position() const { return pos; }

    virtual ~Hitbox() = default;
};

#endif
