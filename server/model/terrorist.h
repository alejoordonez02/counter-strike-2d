#ifndef TERRORIST_H
#define TERRORIST_H

#include "player.h"
#include "tt_equipment.h"

class Terrorist: public Player {
private:
    TTEquipment equipment;

public:
    Terrorist();

    virtual void plant_bomb() override;
    virtual void stop_planting() override;
};

#endif
