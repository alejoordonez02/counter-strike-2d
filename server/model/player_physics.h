#ifndef PLAYER_PHYSICS_H
#define PLAYER_PHYSICS_H

#include <optional>

#include "common/position.h"

#include "hitbox.h"
#include "map.h"
#include "trajectory.h"

class PlayerPhysics: public Hitbox {
private:
    Direction dir;
    float v;
    float a;
    float radius;

protected:
    Map& map;

public:
    PlayerPhysics(const Position& pos, const Direction& dir, float velocity, float acceleration,
                  float radius, Map& map):
            Hitbox(pos), dir(dir), v(velocity), a(acceleration), radius(radius), map(map) {}

    /*
     * Genera la trayectoria del movimiento para checkear si colisiona con algún elemento
     * en el mapa. En caso de colisión, ajusta la posición hasta donde puede. En caso de
     * no haber colisión, ajusta la posición hasta el final de la trayectoria
     * */
    virtual void move(const Direction& dir) {
        float dt = 1;
        auto destination = pos + dir * (v * dt + 0.5 * a * dt * dt);
        Trajectory t(pos /* + dir * radius */ /* prevent player from getting stuck */, destination,
                     radius);
        auto& collidable = map.get_collidable();
        auto sorted_idx = sort_by_distance_idx(collidable);
        for (size_t i: sorted_idx) {
            auto& c = collidable[i];
            if (c.get() == this)
                continue;  // skip self

            if (auto intersection = c->intersect(t)) {
                pos = *intersection - dir * radius;
                return;
            }
        }

        pos = destination;
    }

    /*
     * Calcula el punto más cercano al segmento de recta definido por la trayectoria y luego
     * checkea si la distancia al mismo resulta menor al radio del jugador
     * */
    virtual std::optional<Position> intersect(const Trajectory& trajectory) override {
        auto dir = trajectory.get_direction();
        float t = std::clamp((pos - trajectory.origin).dot(dir) / trajectory.get_length(), 0.0f,
                             1.0f);
        Position closest = trajectory.eval(t);
        auto distance = (closest - pos).get_length();
        Direction to_closest = pos.get_direction(closest);
        if (distance - trajectory.get_width(t, to_closest * (-1)) > radius)
            return std::nullopt;

        Position intersection = pos + to_closest * radius;
        return intersection;
    }


    virtual void get_attacked(const int& damage) override { return (void)damage; }
};

#endif
