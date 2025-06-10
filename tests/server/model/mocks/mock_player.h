#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include <memory>

#include "common/direction.h"
#include "gmock/gmock.h"
#include "server/model/equipment.h"
#include "server/model/player.h"
#include "server/model/weapons.h"

class MockPlayer: public Player {
    public:
    MockPlayer(Position& pos, Map& map):
            Player(pos,
                   Equipment(std::make_unique<Fist>(), std::make_unique<Fist>(),
                             std::make_unique<Fist>(), 0),
                   map) {}

    MockPlayer():
            Player(default_pos(),
                   Equipment(std::make_unique<Fist>(), std::make_unique<Fist>(),
                             std::make_unique<Fist>(), 0),
                   default_map()) {}

    MOCK_METHOD(void, start_moving, (Direction dir), (override));
    MOCK_METHOD(void, start_attacking, (), (override));
    virtual ~MockPlayer() = default;

    private:
    static Position& default_pos() {
        static Position pos(0, 0);
        return pos;
    }
    static Map& default_map() {
        static Map map;
        return map;
    }
    void teleport_to_spawn() override {}
};

#endif
