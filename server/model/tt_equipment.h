#ifndef TT_EQUIPMENT_H
#define TT_EQUIPMENT_H

#include "bomb.h"
#include "equipment.h"

class TTEquipment: public Equipment {
private:
    Bomb bomb;

public:
    TTEquipment(): Equipment(), bomb() {}
};

#endif
