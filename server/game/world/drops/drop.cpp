#include "drop.h"

#include "common/position.h"

Drop::Drop(Position pos): radius(DROP_RADIUS), pos(pos) {}

/*
 * TODO: misma lógica que en PlayerPhysics::intersects, a lo mejor
 * implementar Circle y que ambas hereden de ahí
 * */
bool Drop::intersects(const Position& pos) const {
    float distance = this->pos.get_distance(pos);
    return distance < radius;
}
