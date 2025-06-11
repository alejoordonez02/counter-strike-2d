#ifndef MOCK_PLAYER_PHYSICS_H
#define MOCK_PLAYER_PHYSICS_H

#include "common/position.h"
#include "gmock/gmock.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"

class MockPlayerPhysics: public PlayerPhysics {
    public:
    MockPlayerPhysics(Position& pos, int& health = default_health(),
                      const float& shield = default_shield(),
                      bool& alive = default_alive(), float max_v = 1.0f,
                      float a = 1.0f, float radius = 1.0f,
                      Map& map = default_map()):
            PlayerPhysics(pos, health, shield, alive, max_v, a, radius, map) {}

    MOCK_METHOD(void, get_attacked, (int), (override));

    virtual ~MockPlayerPhysics() = default;

    private:
    static int& default_health() {
        static int health = 100;
        return health;
    }
    static float& default_shield() {
        static float shield = 0.0f;
        return shield;
    }
    static bool& default_alive() {
        static bool alive = true;
        return alive;
    }
    static Map& default_map() {
        static Map map;
        return map;
    }
};

#endif
