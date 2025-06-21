#ifndef SERVER_MODEL_OUNTER_TERRORIST_H
#define SERVER_MODEL_OUNTER_TERRORIST_H

#include "player.h"

class CounterTerrorist: public Player {
private:
    void teleport_to_spawn() override;

public:
    CounterTerrorist(int id, std::weak_ptr<Map> map, float max_velocity,
                     float acceleration, float radius, int money, int health);

    void defuse_bomb() override;
    void stop_defusing() override;
};

#endif
