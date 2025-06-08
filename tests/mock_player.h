#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include "../common/direction.h"
#include "../common/position.h"
#include "../server/model/player.h"
#include "gmock/gmock.h"

#include "equipment.h"
#include "weapons.h"

class MockPlayer: public Player {
private:
    static Position dummy_pos;
    static Map dummy_map;

public:
    MockPlayer():
            Player(dummy_pos,
                   Equipment(std::make_unique<Fist>(), std::make_unique<Fist>(),
                             std::make_unique<Fist>(), 0),
                   dummy_map) {}
    MockPlayer(const Position& pos):
            Player(pos,
                   Equipment(std::make_unique<Fist>(), std::make_unique<Fist>(),
                             std::make_unique<Fist>(), 0),
                   dummy_map) {}
    MOCK_METHOD(void, move, (const Direction&), (override));
    MOCK_METHOD(void, attack, (const Position&), (override));
    MOCK_METHOD(void, get_attacked, (const int&), (override));
    virtual ~MockPlayer() = default;
};

#endif
