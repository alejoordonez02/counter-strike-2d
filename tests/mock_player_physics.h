#ifndef MOCK_PLAYER_PHYSICS_H
#define MOCK_PLAYER_PHYSICS_H

#include "common/position.h"
#include "gmock/gmock.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"

class MockPlayerPhysics: public PlayerPhysics {
private:
    static Position dummy_pos;
    static int dummy_health;
    static float dummy_shield;
    static bool dummy_alive;
    static Map dummy_map;

public:
    MockPlayerPhysics(Position& pos):
            PlayerPhysics(pos, dummy_health, dummy_shield, dummy_alive, 0, 0, 0, dummy_map) {}
    MOCK_METHOD(void, get_attacked, (int), (override));
    virtual ~MockPlayerPhysics() = default;
};

#endif
