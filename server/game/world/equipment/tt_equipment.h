#ifndef SERVER_MODEL_TT_EQUIPMENT_H
#define SERVER_MODEL_TT_EQUIPMENT_H

#include "equipment.h"
#include "weapons.h"

/*
 * Ésta clase probablemente vuele, la idea era poder distinguir los
 * equipamientos de tt y ct, pero por ahora no hay y por lo tanto queda obsoleta
 * */
class TTEquipment: public Equipment {
private:
public:
    TTEquipment(): Equipment(Ak47(), Glock(), 0) {}
};

#endif
