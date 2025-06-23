#include "bomb.h"

Bomb::Bomb(Position pos, float time_left):
    pos(pos), timer(time_left), state(BombState::NOT_PLANTED) {}

void Bomb::update(float dt) {
    if (state == BombState::PLANTED) timer.update(dt);
    if (timer.is_done()) state = BombState::EXPLODED;
}

void Bomb::plant() {
    if (state == BombState::NOT_PLANTED) state = BombState::PLANTED;
}

void Bomb::defuse() {
    if (state == BombState::PLANTED) state = BombState::DEFUSED;
}

bool Bomb::is_planted() const { return state == BombState::PLANTED; }
bool Bomb::is_defused() const { return state == BombState::DEFUSED; }
bool Bomb::has_exploded() const { return state == BombState::EXPLODED; }
