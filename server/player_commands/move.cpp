#include "move.h"

Move::Move(Direction d): dir(d) {}

void Move::execute(Player& p) const { p.move(dir); }
Direction Move::get_dir() const { return dir; }
