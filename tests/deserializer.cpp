#include "../common/network/deserializer.h"

#include <cstdint>
#include <string>

#include "../common/direction.h"
#include "../common/network/protocol.h"
#include "../common/player_commands/attack.h"
#include "../common/player_commands/move.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "mock_player.h"

using ::testing::HasSubstr;
using ::testing::NotNull;
using ::testing::ThrowsMessage;

namespace {
TEST(DeserializerTest, DeserializeValidMoveCommandNorth) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00 /* 0 */,
                                      0x3f,
                                      0x80,
                                      0x00,
                                      0x00 /* 1*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(0, 1)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandNorthEast) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3 /* 1/sqrt(2) */,
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3 /* 1/sqrt(2)*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(1 / std::sqrt(2), 1 / std::sqrt(2))));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandEast) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0x3f,
                                      0x80,
                                      0x00,
                                      0x00 /* 1 */,
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00 /* 0*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(1, 0)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouthEast) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3 /* 1/sqrt(2) */,
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3 /* -1/sqrt(2)*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(1 / std::sqrt(2), -1 / std::sqrt(2))));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouth) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00 /* 0 */,
                                      0xbf,
                                      0x80,
                                      0x00,
                                      0x00 /* -1*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(0, -1)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouthWest) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3 /* -1/sqrt(2) */,
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3 /* -1/sqrt(2)*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(-1 / std::sqrt(2), -1 / std::sqrt(2))));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandWest) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0xbf,
                                      0x80,
                                      0x00,
                                      0x00 /* -1 */,
                                      0x00,
                                      0x00,
                                      0x00,
                                      0x00 /* 0*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(-1, 0)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandNorthWest) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::MOVE,
                                      0xbf,
                                      0x35,
                                      0x04,
                                      0xf3 /* -1/sqrt(2) */,
                                      0x3f,
                                      0x35,
                                      0x04,
                                      0xf3 /* 1/sqrt(2)*/};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(-1 / std::sqrt(2), 1 / std::sqrt(2))));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidAttackCommandWithPositionXPiYPi) {
    std::vector<uint8_t> srlzd_cmd = {PlayerCommandSerial::ATTACK,
                                      0x40,
                                      0x49,
                                      0x0f,
                                      0xdb /* ~pi */,
                                      0x40,
                                      0x49,
                                      0x0f,
                                      0xdb /* ~pi */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Attack* attack_cmd = dynamic_cast<Attack*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, attack(Position(3.14159265, 3.14159265)));
    attack_cmd->execute(p);
}

}  // namespace
