#ifndef SERVER_WORLD_EQUIPMENT_CT_EQUIPMENT_H
#define SERVER_WORLD_EQUIPMENT_CT_EQUIPMENT_H

#include "equipment.h"
#include "weapons.h"

/*
 * Ésta clase probablemente vuele, la idea era poder distinguir los
 * equipamientos de tt y ct, pero por ahora no hay y por lo tanto queda obsoleta
 * */
class CTEquipment: public Equipment {
public:
    CTEquipment(): Equipment(Ak47(), Glock(), 0) {}
};

#endif
