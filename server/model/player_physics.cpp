#include "server/model/player_physics.h"

#include <algorithm>
#include <numeric>
#include <optional>
#include <vector>

#include "common/position.h"
#include "server/model/hitbox.h"
#include "server/model/trajectory.h"

/*
 * Esto no va a la config porque es algo más propio del algoritmo de colisiones,
 * no se debería cambiar por fuera del desarrollo del motor de físicas
 * */
#define MAX_COLLISIONS 1

/*
 * Get distance to a hitbox
 * */
float PlayerPhysics::get_distance(const std::shared_ptr<Hitbox>& hitbox) const {
    return pos.get_distance(hitbox->get_position());
}

/*
 * Sort collidables idx
 * */
void PlayerPhysics::sort_by_distance_idx(
    const std::vector<std::shared_ptr<Hitbox>>& collidables,
    std::vector<size_t>& idx) const {
    if (collidables.size() == 0) return;

    std::vector<size_t> sorted_idx(collidables.size());
    std::iota(sorted_idx.begin(), sorted_idx.end(), 0);
    std::sort(sorted_idx.begin(), sorted_idx.end(),
              [&collidables, this](size_t i, size_t j) {
                  return get_distance(collidables[i]) <
                         get_distance(collidables[j]);
              });

    sorted_idx.erase(sorted_idx.begin());  // skip self
    idx = sorted_idx;
}

/*
 * Move
 * */
void PlayerPhysics::move(float dt) {
    v = std::clamp(v + a * dt, v, max_v);
    Position dest = pos + dir * v * dt;
    Trajectory t(pos + dir * radius / 2, dest, radius);
    int count = 0;
    for (size_t i : sorted_idx) {
        auto c = collidables[i];
        if (auto x = c->intersect(t)) {
            dest = *x + x->get_direction(dest) * radius;
            count++;
        }
        if (count >= MAX_COLLISIONS) break;
    }

    pos = dest;
}

/*
 * Constructor
 * */
PlayerPhysics::PlayerPhysics(Position& pos, float max_velocity,
                             float acceleration, float radius,
                             std::vector<std::shared_ptr<Hitbox>>& collidables,
                             std::vector<size_t>& sorted_idx):
    pos(pos), dir(), max_v(max_velocity), v(0), a(acceleration), radius(radius),
    moving(false), collidables(collidables), sorted_idx(sorted_idx) {}

/*
 * Update
 * */
void PlayerPhysics::update(float dt) {
    sort_by_distance_idx(collidables, sorted_idx);
    if (moving) move(dt);
}

/*
 * Start and stop moving
 * */
bool PlayerPhysics::is_moving() const { return moving; }

void PlayerPhysics::start_moving(const Direction& dir) {
    this->dir = dir;
    moving = true;
}

void PlayerPhysics::stop_moving() {
    v = 0;
    moving = false;
}

/*
 * Get intersection with a trajectory
 * */
std::optional<Position> PlayerPhysics::intersect(const Trajectory& t) const {
    auto closest = t.get_outter_and_inner_closest(pos);
    float distance = pos.get_distance(closest.first);
    if (distance > radius) return std::nullopt;
    auto intersection = pos + pos.get_direction(closest.second) * radius;
    return intersection;
}
