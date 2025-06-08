#include <vector>
#include <cstdint>

#include "../common/network/protocol.h"
#include "../common/network/dtos/start_moving_dto.h"
#include "../common/network/dtos/start_attacking_dto.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::HasSubstr;
using ::testing::NotNull;
using ::testing::ThrowsMessage;

namespace {
TEST(SerializationTest, SerializeMoveCommandNorth) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0x00, 0x00, 0x00, 0x00, // 0
                                         0x3f, 0x80, 0x00, 0x00}; // 1
    MoveDTO dto = MoveDTO(Direction(0, 1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandNorthEast) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0x3f, 0x35, 0x04, 0xf3, // 1/sqrt(2)
                                         0x3f, 0x35, 0x04, 0xf3}; // 1/sqrt(2)
    MoveDTO dto = MoveDTO(Direction(1, 1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandEast) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0x3f, 0x80, 0x00, 0x00, // 1
                                         0x00, 0x00, 0x00, 0x00}; // 0
    MoveDTO dto = MoveDTO(Direction(1, 0));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandSouthEast) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0x3f, 0x35, 0x04, 0xf3, // 1/sqrt(2)
                                         0xbf, 0x35, 0x04, 0xf3}; // -1/sqrt(2)
    MoveDTO dto = MoveDTO(Direction(1, -1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandSouth) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0x00, 0x00, 0x00, 0x00, // 0
                                         0xbf, 0x80, 0x00, 0x00}; // -1
    MoveDTO dto = MoveDTO(Direction(0, -1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandSouthWest) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0xbf, 0x35, 0x04, 0xf3, // -1/sqrt(2)
                                         0xbf, 0x35, 0x04, 0xf3}; // -1/sqrt(2)
    MoveDTO dto = MoveDTO(Direction(-1, -1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandWest) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0xbf, 0x80, 0x00, 0x00, // -1
                                         0x00, 0x00, 0x00, 0x00}; // 0
    MoveDTO dto = MoveDTO(Direction(-1, 0));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandNorthWest) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::MOVE,
                                         0xbf, 0x35, 0x04, 0xf3, // -1/sqrt(2)
                                         0x3f, 0x35, 0x04, 0xf3}; // 1/sqrt(2)
    MoveDTO dto = MoveDTO(Direction(-1, 1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeAttackCommandWithPositionXPiYPi) {
    std::vector<uint8_t> expected_srl = {DTOSerial::PlayerCommands::ATTACK,
                                         0x40, 0x49, 0x0f, 0xdb, // ~pi
                                         0x40, 0x49, 0x0f, 0xdb}; // ~pi
    AttackDTO dto = AttackDTO(Position(3.14159265, 3.14159265));
    EXPECT_EQ(dto.serialize(), expected_srl);
}
}  // namespace
