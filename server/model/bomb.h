#ifndef BOMB_H
#define BOMB_H

/*
 * este número tiene que ir a una config!
 * */
const int bomb_time = 300;

#include "timer.h"

enum class BombState { NOT_PLANTED, PLANTED, EXPLODED, DEFUSED };

class Bomb {
private:
    Timer timer;
    BombState state;

public:
    Bomb(): timer(bomb_time), state(BombState::NOT_PLANTED) {}

    void tick(const int& time_elapsed) {
        if (state == BombState::PLANTED)
            timer.tick(time_elapsed);
        if (timer.is_done())
            state = BombState::EXPLODED;
    }

    void plant() { state = BombState::PLANTED; }

    void defuse() { state = BombState::DEFUSED; }
};

#endif
