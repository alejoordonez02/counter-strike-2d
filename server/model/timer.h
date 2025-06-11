#ifndef SERVER_MODEL_TIMER_H
#define SERVER_MODEL_TIMER_H

class Timer {
    private:
    float time;
    float time_left;
    bool done;

    public:
    explicit Timer(float time): time(time), time_left(time), done(false) {}

    void update(float dt) {
        if (done)
            return;

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
