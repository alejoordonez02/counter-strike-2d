#include <vector>
#include <cstdint>
#include <memory>

#include "../common/network/protocol.h"
#include "../common/network/dtos/move_dto.h"
#include "../common/network/dtos/attack_dto.h"
#include "../server/player_commands/command.h"
#include "../server/cmd_constructor.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "mock_player.h"

using ::testing::HasSubstr;
using ::testing::NotNull;
using ::testing::ThrowsMessage;

namespace {
TEST(CmdDeserializationTest, DeserializeValidMoveCommandNorth) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0x00, 0x00, 0x00, 0x00, // 0
                                      0x3f, 0x80, 0x00, 0x00}; // 1
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd_p = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(0, 1)));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandNorthEast) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0x3f, 0x35, 0x04, 0xf3, // 1/sqrt(2)
                                      0x3f, 0x35, 0x04, 0xf3}; // 1/sqrt(2)
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(1 / std::sqrt(2), 1 / std::sqrt(2))));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandEast) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0x3f, 0x80, 0x00, 0x00, // 1
                                      0x00, 0x00, 0x00, 0x00}; // 0
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(1, 0)));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandSouthEast) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0x3f, 0x35, 0x04, 0xf3, // 1/sqrt(2)
                                      0xbf, 0x35, 0x04, 0xf3}; // -1/sqrt(2)
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(1 / std::sqrt(2), -1 / std::sqrt(2))));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandSouth) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0x00, 0x00, 0x00, 0x00, // 0
                                      0xbf, 0x80, 0x00, 0x00}; // -1
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(0, -1)));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandSouthWest) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0xbf, 0x35, 0x04, 0xf3, // -1/sqrt(2)
                                      0xbf, 0x35, 0x04, 0xf3}; // -1/sqrt(2)
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(-1 / std::sqrt(2), -1 / std::sqrt(2))));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandWest) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0xbf, 0x80, 0x00, 0x00, // -1
                                      0x00, 0x00, 0x00, 0x00}; // 0
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(-1, 0)));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandNorthWest) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::MOVE,
                                      0xbf, 0x35, 0x04, 0xf3, // -1/sqrt(2)
                                      0x3f, 0x35, 0x04, 0xf3}; // 1/sqrt(2)
    std::unique_ptr<DTO> dto_p = std::make_unique<MoveDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(-1 / std::sqrt(2), 1 / std::sqrt(2))));
    cmd->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidAttackCommandWithPositionXPiYPi) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::ATTACK,
                                      0x40, 0x49, 0x0f, 0xdb, // ~pi
                                      0x40, 0x49, 0x0f, 0xdb}; // ~pi
    std::unique_ptr<DTO> dto_p = std::make_unique<AttackDTO>(srlzd_cmd);
    std::unique_ptr<Command> cmd = CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, attack(Position(3.14159265, 3.14159265)));
    cmd_p->execute(p);
}
}  // namespace
