#ifndef SERVER_MODEL_TT_EQUIPMENT_H
#define SERVER_MODEL_TT_EQUIPMENT_H

#include <memory>

#include "server/world/equipment/bomb.h"
#include "server/world/equipment/equipment.h"
#include "server/world/equipment/weapons.h"

class TTEquipment: public Equipment {
private:
    Bomb bomb;

public:
    TTEquipment():
        Equipment(std::make_unique<Fist>(), std::make_unique<Glock>(),
                  std::make_unique<Knife>(), 0),
        bomb(10) {}
};

#endif
