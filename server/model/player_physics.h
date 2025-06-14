#ifndef SERVER_MODEL_PLAYER_PHYSICS_H
#define SERVER_MODEL_PLAYER_PHYSICS_H

#include <optional>
#include <vector>

#include "common/position.h"
#include "server/model/hitbox.h"
#include "server/model/map.h"

class PlayerPhysics {
private:
    Position& pos;
    Direction dir;
    float max_v;
    float v;
    float a;
    float radius;
    bool moving;
    std::weak_ptr<Map> map;

    float get_distance(const Hitbox& hitbox) const;

    std::vector<size_t> sort_by_distance_idx(
            const std::vector<std::shared_ptr<Hitbox>>& collidables) const;

    void move(float dt);

public:
    PlayerPhysics(Position& pos, float max_velocity, float acceleration,
                  float radius, std::weak_ptr<Map> map);

    void update(float dt);

    bool is_moving() const;

    void start_moving(const Direction& dir);

    void stop_moving();

    /*
     * Retornar un vector de los índices de los collisionables del vector,
     * ordenados de menor a mayor distancia a PlayerPhysics
     * */
    std::vector<size_t> get_distance_sorted_collidables_idx(
            const std::vector<std::shared_ptr<Hitbox>>& collidables) const;

    /*
     * Retornar el punto donde interseca la trayectoria con el exterior del
     * hitbox del jugador
     * */
    std::optional<Position> intersect(const Trajectory& trajectory) const;
};

#endif
