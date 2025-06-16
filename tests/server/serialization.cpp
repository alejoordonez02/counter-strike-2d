#include <cstdint>
#include <vector>

#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "common/network/protocol.h"
#include "gtest/gtest.h"

namespace {
TEST(SerializationTest, SerializeMoveCommandNorth) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0x00,
            0x00,
            0x00,
            0x00,  // 0
            0x3f,
            0x80,
            0x00,
            0x00};  // 1
    StartMovingDTO dto = StartMovingDTO(Direction(0, 1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandNorthEast) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0x3f,
            0x35,
            0x04,
            0xf3,  // 1/sqrt(2)
            0x3f,
            0x35,
            0x04,
            0xf3};  // 1/sqrt(2)
    StartMovingDTO dto = StartMovingDTO(Direction(1, 1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandEast) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0x3f,
            0x80,
            0x00,
            0x00,  // 1
            0x00,
            0x00,
            0x00,
            0x00};  // 0
    StartMovingDTO dto = StartMovingDTO(Direction(1, 0));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandSouthEast) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0x3f,
            0x35,
            0x04,
            0xf3,  // 1/sqrt(2)
            0xbf,
            0x35,
            0x04,
            0xf3};  // -1/sqrt(2)
    StartMovingDTO dto = StartMovingDTO(Direction(1, -1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandSouth) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0x00,
            0x00,
            0x00,
            0x00,  // 0
            0xbf,
            0x80,
            0x00,
            0x00};  // -1
    StartMovingDTO dto = StartMovingDTO(Direction(0, -1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandSouthWest) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0xbf,
            0x35,
            0x04,
            0xf3,  // -1/sqrt(2)
            0xbf,
            0x35,
            0x04,
            0xf3};  // -1/sqrt(2)
    StartMovingDTO dto = StartMovingDTO(Direction(-1, -1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandWest) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0xbf,
            0x80,
            0x00,
            0x00,  // -1
            0x00,
            0x00,
            0x00,
            0x00};  // 0
    StartMovingDTO dto = StartMovingDTO(Direction(-1, 0));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeMoveCommandNorthWest) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_MOVING,
            0xbf,
            0x35,
            0x04,
            0xf3,  // -1/sqrt(2)
            0x3f,
            0x35,
            0x04,
            0xf3};  // 1/sqrt(2)
    StartMovingDTO dto = StartMovingDTO(Direction(-1, 1));
    EXPECT_EQ(dto.serialize(), expected_srl);
}

TEST(SerializationTest, SerializeAttackCommandWithPositionXPiYPi) {
    std::vector<uint8_t> expected_srl = {
            DTOSerial::PlayerCommands::START_ATTACKING};
    StartAttackingDTO dto = StartAttackingDTO();
    EXPECT_EQ(dto.serialize(), expected_srl);
}
}  // namespace
