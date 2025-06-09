#ifndef SERVER_MODEL_CT_EQUIPMENT_H
#define SERVER_MODEL_CT_EQUIPMENT_H

#include <memory>

#include "server/model/equipment.h"
#include "server/model/weapons.h"

class CTEquipment: public Equipment {
    public:
    CTEquipment():
            Equipment(std::make_unique<Fist>(), std::make_unique<Glock>(),
                      std::make_unique<Knife>(), 0) {}
};

#endif
