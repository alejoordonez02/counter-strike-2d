#include "attack.h"

Attack::Attack(const Position& pos): pos(pos) {}

void Attack::execute(Player& p) const { p.attack(pos); }

Position Attack::get_position() const { return pos; }
