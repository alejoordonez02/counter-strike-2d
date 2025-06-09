#ifndef SERVER_MODEL_ACTION_STRATEGY_H
#define SERVER_MODEL_ACTION_STRATEGY_H

/*
 * Action strategy
 * */
class ActionStrategy {
    public:
    virtual void update(float dt) = 0;
    virtual ~ActionStrategy() = default;
};

#endif
