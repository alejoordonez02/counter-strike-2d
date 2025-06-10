#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include <memory>

#include "common/direction.h"
#include "gmock/gmock.h"
#include "server/model/equipment.h"
#include "server/model/player.h"
#include "server/model/weapons.h"

class MockPlayer: public Player {
    private:
    static Position dummy_pos;
    static Map dummy_map;
    void teleport_to_spawn() override {}

    public:
    MockPlayer():
            Player(dummy_pos,
                   Equipment(std::make_unique<Fist>(), std::make_unique<Fist>(),
                             std::make_unique<Fist>(), 0),
                   dummy_map) {}
    explicit MockPlayer(const Position& pos):
            Player(pos,
                   Equipment(std::make_unique<Fist>(), std::make_unique<Fist>(),
                             std::make_unique<Fist>(), 0),
                   dummy_map) {}
    MOCK_METHOD(void, start_moving, (Direction dir), (override));
    MOCK_METHOD(void, start_attacking, (), (override));
    virtual ~MockPlayer() = default;
};

#endif
