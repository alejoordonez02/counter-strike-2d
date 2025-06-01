#ifndef CT_EQUIPMENT_H
#define CT_EQUIPMENT_H

#include "equipment.h"
#include "weapons.h"

class CTEquipment: public Equipment {
public:
    CTEquipment():
            Equipment(std::make_unique<Fist>(), std::make_unique<Glock>(),
                      std::make_unique<Knife>(), 0) {}
};

#endif
