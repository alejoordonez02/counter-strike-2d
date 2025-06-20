#ifndef SERVER_WORLD_ACTIONS_IDLE_H
#define SERVER_WORLD_ACTIONS_IDLE_H

#include "server/world/actions/action_strategy.h"

/*
 * Idle action strategy
 * */
class Idle: public ActionStrategy {
public:
    Idle() = default;
    void update(float /* dt */) override {}
};

#endif
