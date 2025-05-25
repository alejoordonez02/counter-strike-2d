#ifndef DIRECTION_H
#define DIRECTION_H

#include <map>

#include "tuple.h"

enum class Cardinal { N, NE, E, SE, S, SW, W, NW };

namespace {
inline const std::map<Cardinal, Tuple<int>> card_to_tup = {
        {Cardinal::N, Tuple<int>(0, 1)},  {Cardinal::NE, Tuple<int>(1, 1)},
        {Cardinal::E, Tuple<int>(1, 0)},  {Cardinal::SE, Tuple<int>(1, -1)},
        {Cardinal::S, Tuple<int>(0, -1)}, {Cardinal::SW, Tuple<int>(-1, -1)},
        {Cardinal::W, Tuple<int>(-1, 0)}, {Cardinal::NW, Tuple<int>(-1, 1)}};

inline const std::map<Tuple<int>, Cardinal> tup_to_card = [] {
    std::map<Tuple<int>, Cardinal> m;
    for (auto const& [c, t]: card_to_tup) {
        m.emplace(Tuple<int>((int)t.x, (int)t.y), c);
    }
    return m;
}();
}  // namespace

struct Direction: public Tuple<int> {
    Cardinal card;

    Direction(const Cardinal& card):
            Tuple(card_to_tup.at(card).x, card_to_tup.at(card).y), card(card) {}

    Direction(const int& x, const int& y): Tuple(x, y), card(tup_to_card.at(Tuple<int>(x, y))) {}

    bool operator==(const Direction& other) const { return card == other.card; }

    bool operator<(const Direction& other) const { return card < other.card; }
};

#endif
