#ifndef SERVER_MODEL_TIMER_H
#define SERVER_MODEL_TIMER_H

class Timer {
    private:
    int time;
    int time_left;
    bool done;

    public:
    explicit Timer(const int& time): time(time), time_left(time), done(false) {}

    void update(float dt) {
        time_left -= dt;
        if (time_left <= 0)
            done = true;
    }

    void restart() {
        time_left = time;
        done = false;
    }

    bool is_done() const { return done; }
};

#endif
