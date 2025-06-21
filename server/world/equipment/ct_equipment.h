#ifndef SERVER_WORLD_EQUIPMENT_CT_EQUIPMENT_H
#define SERVER_WORLD_EQUIPMENT_CT_EQUIPMENT_H

#include "server/world/equipment/equipment.h"
#include "server/world/equipment/weapons.h"

/*
 * Ésta clase probablemente vuele, la idea era poder distinguir los
 * equipamientos de tt y ct, pero por ahora no hay y por lo tanto queda obsoleta
 * */
class CTEquipment: public Equipment {
public:
    CTEquipment(): Equipment(Fist(), Glock(), 0) {}
};

#endif
