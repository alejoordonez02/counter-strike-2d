#include <cstdint>
#include <memory>
#include <vector>

#include "common/network/dtos/start_attacking_dto.h"
#include "common/network/dtos/start_moving_dto.h"
#include "common/network/protocol.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "server/game/player_commands/player_cmd_constructor.h"
#include "server/game/player_commands/player_command.h"
#include "tests/server/model/mocks/mock_player.h"

namespace {
TEST(CmdDeserializationTest, DeserializeValidMoveCommandNorth) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00,  // 0
                                      0x3f,
                                      0x80,
                                      0x00,
                                      0x00};  // 1
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, start_moving(Direction(0, 1)));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandNorthEast) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3,  // 1/sqrt(2)
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3};  // 1/sqrt(2)
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, start_moving(Direction(1 / std::sqrt(2), 1 / std::sqrt(2))));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandEast) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0x3f,
                                      0x80,
                                      0x00,
                                      0x00,  // 1
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00};  // 0
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, start_moving(Direction(1, 0)));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandSouthEast) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3,  // 1/sqrt(2)
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3};  // -1/sqrt(2)
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p,
                start_moving(Direction(1 / std::sqrt(2), -1 / std::sqrt(2))));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandSouth) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00,  // 0
                                      0xbf,
                                      0x80,
                                      0x00,
                                      0x00};  // -1
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, start_moving(Direction(0, -1)));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandSouthWest) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3,  // -1/sqrt(2)
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3};  // -1/sqrt(2)
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p,
                start_moving(Direction(-1 / std::sqrt(2), -1 / std::sqrt(2))));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandWest) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0xbf,
                                      0x80,
                                      0x00,
                                      0x00,  // -1
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00};  // 0
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, start_moving(Direction(-1, 0)));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidMoveCommandNorthWest) {
    std::vector<uint8_t> srlzd_cmd = {DTOSerial::PlayerCommands::START_MOVING,
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3,  // -1/sqrt(2)
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3};  // 1/sqrt(2)
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartMovingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p,
                start_moving(Direction(-1 / std::sqrt(2), 1 / std::sqrt(2))));
    cmd_p->execute(p);
}

TEST(CmdDeserializationTest, DeserializeValidAttackCommandWithPositionXPiYPi) {
    std::vector<uint8_t> srlzd_cmd = {
        DTOSerial::PlayerCommands::START_ATTACKING,
        0x40,
        0x49,
        0x0f,
        0xdb,  // ~pi
        0x40,
        0x49,
        0x0f,
        0xdb};  // ~pi
    std::vector<uint8_t> bytes = srlzd_cmd;
    std::unique_ptr<DTO> dto_p =
        std::make_unique<StartAttackingDTO>(std::move(bytes));
    std::unique_ptr<Command> cmd_p =
        CmdConstructor().construct(std::move(dto_p));
    MockPlayer p;
    EXPECT_CALL(p, start_attacking());
    cmd_p->execute(p);
}
}  // namespace
