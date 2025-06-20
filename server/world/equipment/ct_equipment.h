#ifndef SERVER_WORLD_EQUIPMENT_CT_EQUIPMENT_H
#define SERVER_WORLD_EQUIPMENT_CT_EQUIPMENT_H

#include <memory>

#include "server/world/equipment/equipment.h"
#include "server/world/equipment/weapons.h"

class CTEquipment: public Equipment {
public:
    CTEquipment():
        Equipment(std::make_unique<Fist>(), std::make_unique<Glock>(),
                  std::make_unique<Knife>(), 0) {}
};

#endif
