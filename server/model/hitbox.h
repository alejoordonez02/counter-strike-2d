#ifndef HITBOX_H
#define HITBOX_H

#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>

#include "trajectory.h"

class Hitbox {
protected:
    Position pos;

public:
    Hitbox(const Position& pos): pos(pos) {}

    virtual const Position& get_position() const { return pos; }

    virtual float get_distance(const Hitbox& hitbox) const { return pos.get_distance(hitbox.pos); }

    virtual bool intersects(const Trajectory& t) = 0;

    virtual void get_attacked(const int& damage) = 0;

    std::vector<size_t> sort_by_distance_idx(
            const std::vector<std::unique_ptr<Hitbox>>& coll) const {
        std::vector<size_t> idx(coll.size());
        std::iota(idx.begin(), idx.end(), 0);

        std::sort(idx.begin(), idx.end(), [&coll, this](size_t i, size_t j) {
            return get_distance(*coll[i]) < get_distance(*coll[j]);
        });
        return idx;
    }

    virtual ~Hitbox() = default;
};

#endif
