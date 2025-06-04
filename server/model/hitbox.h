#ifndef HITBOX_H
#define HITBOX_H

#include <algorithm>
#include <memory>
#include <numeric>
#include <optional>
#include <vector>

#include "trajectory.h"

class Hitbox {
protected:
    Position pos;

    std::vector<size_t> sort_by_distance_idx(
            const std::vector<std::unique_ptr<Hitbox>>& coll) const {
        std::vector<size_t> idx(coll.size());
        std::iota(idx.begin(), idx.end(), 0);

        std::sort(idx.begin(), idx.end(), [&coll, this](size_t i, size_t j) {
            return get_distance(*coll[i]) < get_distance(*coll[j]);
        });
        return idx;
    }

public:
    Hitbox(const Position& pos): pos(pos) {}

    virtual const Position& get_position() const { return pos; }

    virtual float get_distance(const Hitbox& hitbox) const { return pos.get_distance(hitbox.pos); }

    virtual std::optional<Position> intersect(const Trajectory& t) = 0;

    virtual void get_attacked(const int& damage) = 0;

    virtual ~Hitbox() = default;
};

#endif
