#ifndef SERVER_WORLD_PHYSICS_PLAYER_PHYSICS_H
#define SERVER_WORLD_PHYSICS_PLAYER_PHYSICS_H

#include <memory>
#include <optional>
#include <vector>

#include "common/position.h"
#include "hitbox.h"

class PlayerPhysics {
private:
    Position& pos;
    Direction dir;
    float max_v;
    float v;
    float a;
    float radius;
    bool moving;
    std::vector<std::shared_ptr<Hitbox>>& collidables;
    std::vector<size_t>& sorted_idx;

    float get_distance(const std::shared_ptr<Hitbox>& hitbox) const;

    void sort_by_distance_idx(
        const std::vector<std::shared_ptr<Hitbox>>& collidables,
        std::vector<size_t>& idx) const;

    void move(float dt);

public:
    PlayerPhysics(Position& pos, float max_velocity, float acceleration,
                  float radius,
                  std::vector<std::shared_ptr<Hitbox>>& collidables,
                  std::vector<size_t>& sorted_idx);

    void update(float dt);

    bool is_moving() const;

    void start_moving(const Direction& dir);

    void stop_moving();

    std::optional<Position> intersect(const Trajectory& trajectory) const;

    bool intersects(const Position& pos) const;
};

#endif
