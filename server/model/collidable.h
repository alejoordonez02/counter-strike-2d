#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

#include "../../common/position.h"  // pos debería ser de model xd

/*
 * Player va a implementar Collidable
 * */
class Collidable {
private:
    Position pos;

public:
    Position get_pos() const { return pos; }
    virtual void get_attacked(const int& damage) = 0;

    std::vector<size_t> sort_by_distance_idx(const std::vector<Collidable>& coll) const {
        std::vector<size_t> idx(coll.size());
        std::iota(idx.begin(), idx.end(), 0);

        std::sort(idx.begin(), idx.end(), [&coll, this](size_t i, size_t j) {
            return get_distance(coll[i]) < get_distance(coll[j]);
        });
        return idx;
    }

    float get_distance(const Collidable& coll) const {
        float dx = pos.x - coll.pos.x;
        float dy = pos.y - coll.pos.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    virtual ~Collidable();
};

#endif
