#ifndef SERVER_MODEL_OUNTER_TERRORIST_H
#define SERVER_MODEL_OUNTER_TERRORIST_H

#include "server/model/ct_equipment.h"
#include "server/model/player.h"

class CounterTerrorist: public Player {
    private:
    void teleport_to_spawn() override { pos = map.get_ct_spawn(); }

    public:
    CounterTerrorist(const Position& pos, Map& map):
            Player(pos, CTEquipment(), map) {}

    void defuse_bomb() override;
    void stop_defusing() override;
};

#endif
