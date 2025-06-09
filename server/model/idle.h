#ifndef SERVER_MODEL_IDLE_H
#define SERVER_MODEL_IDLE_H

#include "server/model/action_strategy.h"

/*
 * Idle
 * */
class Idle: public ActionStrategy {
    public:
    Idle() = default;
    void update(float /* dt */) override {}
};

#endif
