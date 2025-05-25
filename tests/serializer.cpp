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
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::N)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::N};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandNorthEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::NE)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::NE};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::E)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::E};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandSouthEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::SE)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::SE};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandSouth) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::S)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::S};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandSouthWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::SW)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::SW};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::W)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::W};
    EXPECT_EQ(srl, expected_srl);
}

TEST(SerializerTest, SerializeMoveCommandNorthWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction(Cardinal::NW)));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, CardinalSerial::NW};
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
