#include "attack.h"

Attack::Attack(Direction& dir, Weapon& weapon): dir(dir), weapon(weapon) {}
void Attack::update(float dt) { (void)dir; }
