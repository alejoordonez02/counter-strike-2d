#ifndef POSITION_H
#define POSITION_H

#include "tuple.h"

struct Position: public Tuple<float> {
    Position(const float& x, const float& y): Tuple(x, y) {}
};

#endif
