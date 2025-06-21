#ifndef SERVER_WORLD_EQUIPMENT_BOMB_H
#define SERVER_WORLD_EQUIPMENT_BOMB_H

#include "server/world/timer.h"

enum class BombState { NOT_PLANTED, PLANTED, EXPLODED, DEFUSED };

class Bomb {
private:
    Timer timer;
    BombState state;

public:
    Bomb(float time_left);

    void update(float dt);

    void plant();

    void defuse();

    bool is_planted() const;

    bool is_defused() const;

    bool has_exploded() const;
};

#endif
