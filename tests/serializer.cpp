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
TEST(DeserializerTest, SerializeMoveCommandNorth) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::N));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::N};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandNorthEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::NE));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::NE};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::E));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::E};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandSouthEast) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::SE));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::SE};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandSouth) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::S));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::S};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandSouthWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::SW));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::SW};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::W));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::W};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeMoveCommandNorthWest) {
    std::vector<uint8_t> srl = Serializer::serialize(Move(Direction::NW));
    std::vector<uint8_t> expected_srl = {PlayerCommandSerial::MOVE, DirectionSerial::NW};
    EXPECT_EQ(srl, expected_srl);
}

TEST(DeserializerTest, SerializeAttackCommandWithPositionXPiYPi) {
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
