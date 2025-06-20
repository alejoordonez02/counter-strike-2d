#ifndef SERVER_WORLD_TERRORIST_H
#define SERVER_WORLD_TERRORIST_H

#include "server/world/equipment/tt_equipment.h"
#include "server/world/player.h"

class Terrorist: public Player {
private:
    void teleport_to_spawn() override { pos = map.get_tt_spawn(); }

public:
    Terrorist(const Position& pos, Map& map): Player(pos, TTEquipment(), map) {}

    void plant_bomb() override {}
    void stop_planting() override {}
};

#endif
