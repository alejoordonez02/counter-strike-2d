#ifndef MOCK_PLAYER_PHYSICS_H
#define MOCK_PLAYER_PHYSICS_H

#include <optional>
#include <vector>

#include "common/direction.h"
#include "common/position.h"
#include "gmock/gmock.h"
#include "server/model/hitbox.h"
#include "server/model/map.h"
#include "server/model/player_physics.h"
#include "server/model/trajectory.h"

class MockPlayerPhysics: public PlayerPhysics {
private:
    static Position& default_ops() {
        static Position pos{0.0f, 0.0f};
        return pos;
    }

    static Map& default_map() {
        static Map map;
        return map;
    }

    static float default_max_velocity() { return 1.0f; }

    static float default_acceleration() { return 1.0f; }

    static float default_radius() { return 1.0f; }

public:
    MockPlayerPhysics(Position& pos, float max_v = 1.0f, float accel = 1.0f,
                      float r = 1.0f, Map& map_instance = default_map()):
            PlayerPhysics(pos, max_v, accel, r, map_instance) {}

    MockPlayerPhysics(Position& pos, Map& map):
            PlayerPhysics(pos, default_max_velocity(), default_acceleration(),
                          default_radius(), map) {}

    MOCK_METHOD(void, update, (float dt), ());

    MOCK_METHOD(bool, is_moving, (), (const));

    MOCK_METHOD(void, start_moving, (const Direction& dir), ());

    MOCK_METHOD(void, stop_moving, (), ());

    MOCK_METHOD(
            (std::vector<size_t>), get_distance_sorted_collidables_idx,
            (const std::vector<std::reference_wrapper<Hitbox>>& collidables),
            (const override));

    MOCK_METHOD(std::optional<Position>, intersect,
                (const Trajectory& trajectory), (const override));

    virtual ~MockPlayerPhysics() = default;
};

#endif
