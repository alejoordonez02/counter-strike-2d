#ifndef MOCK_PLAYER_H
#define MOCK_PLAYER_H

#include "../common/direction.h"
#include "../common/position.h"
#include "../server/model/player.h"
#include "gmock/gmock.h"

// class PlayerInterface {
// public:
//     virtual void move(const Direction& dir) = 0;
//     virtual void attack(const int& angle) = 0;
//     virtual ~PlayerInterface() = default;
// };

class MockPlayer: public Player {
public:
    MOCK_METHOD(void, move, (const Direction&), (override));
    MOCK_METHOD(void, attack, (const Position&), (override));
    virtual ~MockPlayer() = default;
};

#endif
