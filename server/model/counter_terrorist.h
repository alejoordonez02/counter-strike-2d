#ifndef COUNTER_TERRORIST_H
#define COUNTER_TERRORIST_H

#include "ct_equipment.h"
#include "player.h"

class CounterTerrorist: public Player {
public:
    CounterTerrorist(const Position& pos, Map& map): Player(pos, CTEquipment(), map) {}

    virtual void defuse_bomb() override;
    virtual void stop_defusing() override;
};

#endif
