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
    float max_v;
    float v;
    float a;
    float radius;
    int& health;
    const float& shield;
    bool& alive;
    bool moving;
    Map& map;

    void move(float dt) {
        /*
         * Genera la trayectoria del movimiento para checkear si colisiona con algún elemento
         * en el mapa. En caso de colisión, ajusta la posición hasta donde puede. En caso de
         * no haber colisión, ajusta la posición hasta el final de la trayectoria
         * */
        v += 0.5 * a * dt * dt;
        if (v > max_v)
            v = max_v;

        Position destination = pos + dir * v;

        Trajectory t(pos, destination, radius);
        auto& collidable = map.get_collidable();
        auto sorted_idx = sort_by_distance_idx(collidable);
        for (size_t i: sorted_idx) {
            auto& c = collidable[i];
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

public:
    PlayerPhysics(Position& pos, int& health, const float& shield, bool& alive, float max_velocity,
                  float acceleration, float radius, Map& map):
            Hitbox(pos),
            dir(),
            max_v(max_velocity),
            v(0),
            a(acceleration),
            radius(radius),
            health(health),
            shield(shield),
            alive(alive),
            moving(false),
            map(map) {}

    void update(float dt) {
        if (moving)
            move(dt);
    }

    void start_moving(const Direction& dir) {
        this->dir = dir;
        moving = true;
    }

    void stop_moving() { moving = false; }

    /*
     * Retornar un vector de punteros a collisionables ordenados por distancia a PlayerPhysics
     * */
    std::vector<size_t> get_distance_sorted_collidables_idx(
            const std::vector<std::unique_ptr<Hitbox>>& collidables) const {
        return sort_by_distance_idx(collidables);
    }

    /*
     * Hitbox overrides
     * */
    std::optional<Position> intersect(const Trajectory& trajectory) const override {
        /*
         * Calcula el punto más cercano al segmento de recta definido por la trayectoria y luego
         * checkea si la distancia al mismo resulta menor al radio del jugador
         * */
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

    virtual void get_attacked(int damage) override {
        health -= (1 - shield) * damage;
        if (health <= 0)
            alive &= 0;
    }
};

#endif
