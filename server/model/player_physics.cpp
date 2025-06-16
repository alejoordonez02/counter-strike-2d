#include "server/model/player_physics.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

#include "common/position.h"
#include "server/model/hitbox.h"
#include "server/model/trajectory.h"

float PlayerPhysics::get_distance(const std::shared_ptr<Hitbox>& hitbox) const {
    return pos.get_distance(hitbox->get_position());
}

/*
 * Esto es muy caro, se hace encima en cada update de Player... pero la otra
 * opción viable (por lo menos que se me ocurra ahora) es rediseñar todo para
 * que Map maneje las colisiones, si el juego anda mal es derecho ir a hacer
 * eso, si no puede esperar hasta que haya tiempo
 * */
void PlayerPhysics::sort_by_distance_idx(
        const std::vector<std::shared_ptr<Hitbox>>& collidables,
        std::vector<size_t>& idx) const {
    if (collidables.size() == 0)
        return;

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
    for (size_t i : sorted_idx) {
        auto c = collidables[i];
        if (auto intersection = c->intersect(t)) {
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
                             float acceleration, float radius,
                             std::vector<std::shared_ptr<Hitbox>>& collidables,
                             std::vector<size_t>& sorted_idx):
        pos(pos),
        dir(),
        max_v(max_velocity),
        v(0),
        a(acceleration),
        radius(radius),
        moving(false),
        collidables(collidables),
        sorted_idx(sorted_idx) {}

bool PlayerPhysics::is_moving() const { return moving; }

void PlayerPhysics::update(float dt) {
    sort_by_distance_idx(collidables, sorted_idx);
    if (moving)
        move(dt);
}

void PlayerPhysics::start_moving(const Direction& dir) {
    std::cout << "PlayerPhysics: started moving\n";
    this->dir = dir;
    moving = true;
}

void PlayerPhysics::stop_moving() {
    std::cout << "PlayerPhysics: stopped moving\n";
    v = 0;
    moving = false;
}

std::optional<Position> PlayerPhysics::intersect(
        const Trajectory& trajectory) const {
    /*
     * Calcula el punto más cercano al segmento de recta definido por la
     * trayectoria y luego checkea si la distancia al mismo resulta menor al
     * radio del jugador
     * */
    auto dir = trajectory.get_direction();
    auto length = trajectory.get_length();
    /*
     * Esto de length == 0 obviamente está mal
     * */
    if (length == 0)
        return std::nullopt;

    float t =
            std::clamp((pos - trajectory.origin).dot(dir) / length, 0.0f, 1.0f);
    Position closest = trajectory.eval(t);
    auto distance = (closest - pos).get_length();
    Direction to_closest = pos.get_direction(closest);
    if (distance - trajectory.get_width(t, to_closest * (-1)) > radius)
        return std::nullopt;

    Position intersection = pos + to_closest * radius;
    return intersection;
}
