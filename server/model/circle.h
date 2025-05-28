#ifndef CIRCLE_H
#define CIRCLE_H

#include "../../common/position.h"

#include "hitbox.h"

class Circle: public Hitbox {
private:
    float radius;

public:
    Circle(const Position& pos, const float& radius): Hitbox(pos), radius(radius) {}

    virtual bool intersects(const Trajectory& trajectory) override {
        auto dir = trajectory.get_direction();
        float t = std::clamp((pos - trajectory.origin).dot(dir) / trajectory.get_length(), 0.0f,
                             1.0f);
        Position closest = trajectory.eval(t);
        auto distance = (pos - closest).get_length();
        return distance <= radius;
    }
};

#endif
