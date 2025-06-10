#ifndef SERVER_MODEL_OMB_H
#define SERVER_MODEL_OMB_H

/*
 * este número tiene que ir a una config!
 * */
const int bomb_time = 300;

#include "server/model/timer.h"

enum class BombState { NOT_PLANTED, PLANTED, EXPLODED, DEFUSED };

class Bomb {
    private:
    Timer timer;
    BombState state;

    public:
    Bomb(float time_left): timer(time_left), state(BombState::NOT_PLANTED) {}

    void update(float dt) {
        if (state == BombState::PLANTED)
            timer.update(dt);

        if (timer.is_done())
            state = BombState::EXPLODED;
    }

    void plant() {
        if (state == BombState::NOT_PLANTED)
            state = BombState::PLANTED;
    }

    void defuse() {
        if (state == BombState::PLANTED)
            state = BombState::DEFUSED;
    }

    bool is_planted() const { return state == BombState::PLANTED; }

    bool is_defused() const { return state == BombState::DEFUSED; }

    bool has_exploded() const { return state == BombState::EXPLODED; }
};

#endif
