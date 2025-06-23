#ifndef SERVER_WORLD_TERRORIST_H
#define SERVER_WORLD_TERRORIST_H

#include "player.h"

class Terrorist: public Player {
private:
    bool has_bomb;

    void teleport_to_spawn() override;

public:
    Terrorist(int id, std::weak_ptr<Map> map, float max_velocity,
              float acceleration, float radius, int money, int health);

    void switch_side() override {}

    void restart() override;

    void give_bomb() override;

    void plant_bomb() override;

    void defuse_bomb() override {}
};

#endif
