#include "../common/network/serializer.h"

#include <cstdint>

#include "../common/network/protocol.h"
#include "../common/player_commands/attack.h"
#include "../common/player_commands/move.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::HasSubstr;
using ::testing::NotNull;
using ::testing::ThrowsMessage;

namespace {
TEST(SerializerTest, SerializeMoveCommandNorth) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(0, 1)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0x00,
                                         0x00,
                                         0x00,
                                         0x00 /* 0 */,
                                         0x3f,
                                         0x80,
                                         0x00,
                                         0x00 /* 1 */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandNorthEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(1, 1)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0x3f,
                                         0x35,
                                         0x04,
                                         0xf3 /* 1/sqrt(2) */,
                                         0x3f,
                                         0x35,
                                         0x04,
                                         0xf3 /* 1/sqrt(2) */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(1, 0)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0x3f,
                                         0x80,
                                         0x00,
                                         0x00 /* 1 */,
                                         0x00,
                                         0x00,
                                         0x00,
                                         0x00 /* 0 */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandSouthEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(1, -1)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0x3f,
                                         0x35,
                                         0x04,
                                         0xf3 /* 1/sqrt(2) */,
                                         0xbf,
                                         0x35,
                                         0x04,
                                         0xf3 /* -1/sqrt(2) */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandSouth) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(0, -1)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0x00,
                                         0x00,
                                         0x00,
                                         0x00 /* 0 */,
                                         0xbf,
                                         0x80,
                                         0x00,
                                         0x00 /* -1 */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandSouthWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(-1, -1)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0xbf,
                                         0x35,
                                         0x04,
                                         0xf3 /* -1/sqrt(2) */,
                                         0xbf,
                                         0x35,
                                         0x04,
                                         0xf3 /* -1/sqrt(2) */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(-1, 0)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0xbf,
                                         0x80,
                                         0x00,
                                         0x00 /* -1 */,
                                         0x00,
                                         0x00,
                                         0x00,
                                         0x00 /* 0 */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandNorthWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(-1, 1)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE,
                                         0xbf,
                                         0x35,
                                         0x04,
                                         0xf3 /* -1/sqrt(2) */,
                                         0x3f,
                                         0x35,
                                         0x04,
                                         0xf3 /* 1/sqrt(2) */};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeAttackCommandWithPositionXPiYPi) {
    std::vector<uint8_t> srl = Serializer::serialize(Attack(Position(3.14159265, 3.14159265)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::ATTACK,
                                         0x40,
                                         0x49,
                                         0x0f,
                                         0xdb /* ~pi */,
                                         0x40,
                                         0x49,
                                         0x0f,
                                         0xdb /* ~pi */};
    EXPECT_EQ(srl, expected_srl);
}
}  // namespace
