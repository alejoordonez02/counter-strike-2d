#ifndef TERRORIST_H
#define TERRORIST_H

#include "player.h"
#include "tt_equipment.h"

class Terrorist: public Player {
public:
    Terrorist(const Position& pos, Map& map): Player(pos, TTEquipment(), map) {}

    virtual void plant_bomb() override {}
    virtual void stop_planting() override {}
};

#endif
