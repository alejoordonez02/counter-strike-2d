#ifndef TT_EQUIPMENT_H
#define TT_EQUIPMENT_H

#include "bomb.h"
#include "equipment.h"
#include "weapons.h"

class TTEquipment: public Equipment {
private:
    Bomb bomb;

public:
    TTEquipment():
            Equipment(std::make_unique<Fist>(), std::make_unique<Glock>(),
                      std::make_unique<Knife>(), 0),
            bomb() {}
};

#endif
