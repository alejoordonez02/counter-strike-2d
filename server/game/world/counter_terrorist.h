#ifndef SERVER_MODEL_OUNTER_TERRORIST_H
#define SERVER_MODEL_OUNTER_TERRORIST_H

#include "player.h"

class CounterTerrorist: public Player {
private:
    void teleport_to_spawn() override;

public:
    CounterTerrorist(int id, std::shared_ptr<Weapon> primary,
                     std::shared_ptr<Weapon> secondary,
                     std::shared_ptr<Weapon> knife, std::weak_ptr<Map> map,
                     float max_velocity, float acceleration, float radius,
                     int money, int health,
                     std::shared_ptr<WeaponFactory> weapon_factory);

    void switch_side() override {}

    void restart() override;

    void start_defusing() override;

    void give_bomb() override {}
    void start_planting() override {}
};

#endif
