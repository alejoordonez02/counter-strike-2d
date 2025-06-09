#ifndef HITBOX_H
#define HITBOX_H

#include <algorithm>
#include <memory>
#include <numeric>
#include <optional>
#include <vector>

#include "trajectory.h"

class Hitbox {
private:
    float get_distance(const Hitbox& hitbox) const { return pos.get_distance(hitbox.pos); }

protected:
    Position& pos;

    std::vector<size_t> sort_by_distance_idx(
            const std::vector<std::unique_ptr<Hitbox>>& coll) const {
        std::vector<size_t> idx;
        idx.reserve(coll.size());
        for (size_t i = 0; i < coll.size(); ++i) {
            if (coll[i].get() != this)  // skip self
                idx.push_back(i);
        }

        std::sort(idx.begin(), idx.end(), [&coll, this](size_t i, size_t j) {
            return get_distance(*coll[i]) < get_distance(*coll[j]);
        });

        return idx;
    }

public:
    Hitbox(Position& pos): pos(pos) {}

    virtual std::optional<Position> intersect(const Trajectory& t) const = 0;

    virtual void get_attacked(int damage) = 0;

    virtual ~Hitbox() = default;
};

#endif
