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
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x00 /* north */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::N)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandNorthEast) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x01 /* north east */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::NE)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandEast) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x02 /* east */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::E)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouthEast) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x03 /* south east */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::SE)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouth) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x04 /* south */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::S)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouthWest) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x05 /* south west */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::SW)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandWest) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x06 /* west */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::W)));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandNorthWest) {
    std::vector<uint8_t> srlzd_cmd = {0x6d /* move */, 0x07 /* north west */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_CALL(p, move(Direction(Cardinal::NW)));
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
