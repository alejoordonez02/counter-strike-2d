#include "move.h"

Move::Move(Direction d): dir(d) {}

Move::Move() : dir(0, 0) {}

void Move::execute(Player& p) const { p.move(dir); }
Direction Move::get_direction() const { return dir; }
