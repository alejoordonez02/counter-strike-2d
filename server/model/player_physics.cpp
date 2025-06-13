#include "server/model/player_physics.h"

#include <algorithm>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "common/position.h"
#include "server/model/hitbox.h"
#include "server/model/map.h"
#include "server/model/trajectory.h"

float PlayerPhysics::get_distance(const Hitbox& hitbox) const {
    return pos.get_distance(hitbox.get_position());
}

std::vector<size_t> PlayerPhysics::sort_by_distance_idx(
        const std::vector<std::reference_wrapper<Hitbox>>& collidables) const {
    std::vector<size_t> idx;
    idx.reserve(collidables.size());
    for (size_t i = 0; i < collidables.size(); ++i) {
        if (pos == collidables[i].get().get_position())
            continue;  // skip same position

        idx.push_back(i);
    }

    std::sort(idx.begin(), idx.end(), [&collidables, this](size_t i, size_t j) {
        return get_distance(collidables[i]) < get_distance(collidables[j]);
    });

    return idx;
}

void PlayerPhysics::move(float dt) {
    /*
     * Genera la trayectoria del movimiento para checkear si colisiona con
     * algún elemento en el mapa. En caso de colisión, ajusta la posición
     * hasta donde puede. En caso de no haber colisión, ajusta la posición
     * hasta el final de la trayectoria
     * */
    v += 0.5 * a * dt * dt;
    if (v > max_v)
        v = max_v;

    Position destination = pos + dir * v;

    Trajectory t(pos, destination, radius);
    auto& collidable = map.get_collidables();
    auto sorted_idx = sort_by_distance_idx(collidable);
    for (size_t i : sorted_idx) {
        auto& c = collidable[i];
        if (auto intersection = c.get().intersect(t)) {
            pos = *intersection - dir * radius;
            return;
        }
    }

    /*
     * operator= está sobrecargado en Position, la referencia se mantiene
     * */
    pos = destination;
}

PlayerPhysics::PlayerPhysics(Position& pos, float max_velocity,
                             float acceleration, float radius, Map& map):
        pos(pos),
        dir(),
        max_v(max_velocity),
        v(0),
        a(acceleration),
        radius(radius),
        moving(false),
        map(map) {}

bool PlayerPhysics::is_moving() const { return moving; }

void PlayerPhysics::update(float dt) {
    if (moving)
        move(dt);
}

void PlayerPhysics::start_moving(const Direction& dir) {
    this->dir = dir;
    moving = true;
}

void PlayerPhysics::stop_moving() {
    v = 0;
    moving = false;
}

std::vector<size_t> PlayerPhysics::get_distance_sorted_collidables_idx(
        const std::vector<std::reference_wrapper<Hitbox>>& collidables) const {
    return sort_by_distance_idx(collidables);
}

std::optional<Position> PlayerPhysics::intersect(
        const Trajectory& trajectory) const {
    /*
     * Calcula el punto más cercano al segmento de recta definido por la
     * trayectoria y luego checkea si la distancia al mismo resulta menor al
     * radio del jugador
     * */
    auto dir = trajectory.get_direction();
    float t = std::clamp(
            (pos - trajectory.origin).dot(dir) / trajectory.get_length(), 0.0f,
            1.0f);
    Position closest = trajectory.eval(t);
    auto distance = (closest - pos).get_length();
    Direction to_closest = pos.get_direction(closest);
    if (distance - trajectory.get_width(t, to_closest * (-1)) > radius)
        return std::nullopt;

    Position intersection = pos + to_closest * radius;
    return intersection;
}
