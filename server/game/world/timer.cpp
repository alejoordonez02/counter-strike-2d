#include "timer.h"

Timer::Timer(float time): time(time), time_left(time), done(false) {}

void Timer::update(float dt) {
    if (done) return;

    time_left -= dt;
    if (time_left <= 0) done = true;
}

void Timer::restart() {
    time_left = time;
    done = false;
}

bool Timer::is_done() const { return done; }

float Timer::get_time_left() { return time_left; }
