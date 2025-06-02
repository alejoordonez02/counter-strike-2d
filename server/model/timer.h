#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
    int time_left;
    bool done;

public:
    Timer(const int& time_left): time_left(time_left), done(false) {}

    void tick(const int& time_elapsed) {
        time_left -= time_elapsed;
        if (time_left <= 0)
            done = true;
    }

    bool is_done() { return done; }
};

#endif
