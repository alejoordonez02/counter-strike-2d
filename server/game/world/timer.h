#ifndef SERVER_MODEL_TIMER_H
#define SERVER_MODEL_TIMER_H

class Timer {
private:
    float time;
    float time_left;
    bool done;

public:
    explicit Timer(float time);

    void update(float dt);

    void restart();

    bool is_done() const;

    float get_time_left();
};

#endif
