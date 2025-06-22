#ifndef SERVER_WORLD_TERRORIST_H
#define SERVER_WORLD_TERRORIST_H

#include "player.h"

class Terrorist: public Player {
private:
    std::optional<Bomb> bomb;

    void teleport_to_spawn() override;

public:
    Terrorist(int id, std::weak_ptr<Map> map, float max_velocity,
              float acceleration, float radius, int money, int health,
              std::optional<Bomb> bomb);

    void switch_side() override {}

    void plant_bomb() override;
    void stop_planting() override;

    void defuse_bomb() override {}
    void stop_defusing() override {}
};

#endif
