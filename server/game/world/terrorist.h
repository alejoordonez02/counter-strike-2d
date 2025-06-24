#ifndef SERVER_WORLD_TERRORIST_H
#define SERVER_WORLD_TERRORIST_H

#include "player.h"

class Terrorist: public Player {
private:
    bool has_bomb;

    void teleport_to_spawn() override;

public:
    Terrorist(int id, std::shared_ptr<Weapon> primary,
              std::shared_ptr<Weapon> secondary, std::shared_ptr<Weapon> knife,
              std::weak_ptr<Map> map, float max_velocity, float acceleration,
              float radius, int money, int health,
              std::shared_ptr<WeaponFactory> weapon_factory);

    void switch_side() override {}

    void restart() override;

    void give_bomb() override;

    void start_planting() override;

    void start_defusing() override {}
};

#endif
