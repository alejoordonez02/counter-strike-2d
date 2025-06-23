#ifndef SERVER_WORLD_EQUIPMENT_BOMB_H
#define SERVER_WORLD_EQUIPMENT_BOMB_H

#include "position.h"
#include "server/game/world/timer.h"

enum class BombState { NOT_PLANTED, PLANTED, EXPLODED, DEFUSED };

class Bomb {
private:
    Position pos;
    Timer timer;
    BombState state;

public:
    Bomb(Position pos, float time_left);

    void update(float dt);

    void plant();

    BombState get_state() { return state; }

    void defuse();

    bool is_planted() const;

    bool is_defused() const;

    bool has_exploded() const;
};

#endif
