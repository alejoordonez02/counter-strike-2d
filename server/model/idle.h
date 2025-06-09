#ifndef IDLE_H
#define IDLE_H

#include "action_strategy.h"

/*
 * Idle
 * */
class Idle: public ActionStrategy {
public:
    Idle() {};
    void update(float /* dt */) override {}
};

#endif
