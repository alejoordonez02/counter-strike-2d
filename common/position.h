#ifndef POSITION_H
#define POSITION_H

struct Position {
    float x;
    float y;
    Position(const float& x, const float& y): x(x), y(y) {}
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
};

#endif
