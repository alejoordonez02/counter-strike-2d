#ifndef COUNTER_TERRORIST_H
#define COUNTER_TERRORIST_H

#include "equipment.h"
#include "player.h"

class CounterTerrorist: public Player {
private:
    Equipment equipment;

public:
    CounterTerrorist();

    virtual void defuse_bomb() override;
    virtual void stop_defusing() override;
};

#endif
