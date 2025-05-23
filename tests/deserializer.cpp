#include "../common/network/deserializer.h"

#include <cstdint>
#include <string>

#include "../common/direction.h"
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
    std::string srlzd_cmd = {0x6d /* move */, 0x00 /* north */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::N);
    EXPECT_CALL(p, move(Direction::N));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandNorthEast) {
    std::string srlzd_cmd = {0x6d /* move */, 0x01 /* north east */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::NE);
    EXPECT_CALL(p, move(Direction::NE));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandEast) {
    std::string srlzd_cmd = {0x6d /* move */, 0x02 /* east */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::E);
    EXPECT_CALL(p, move(Direction::E));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouthEast) {
    std::string srlzd_cmd = {0x6d /* move */, 0x03 /* south east */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::SE);
    EXPECT_CALL(p, move(Direction::SE));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouth) {
    std::string srlzd_cmd = {0x6d /* move */, 0x04 /* south */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::S);
    EXPECT_CALL(p, move(Direction::S));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandSouthWest) {
    std::string srlzd_cmd = {0x6d /* move */, 0x05 /* south west */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::SW);
    EXPECT_CALL(p, move(Direction::SW));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandWest) {
    std::string srlzd_cmd = {0x6d /* move */, 0x06 /* west */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::W);
    EXPECT_CALL(p, move(Direction::W));
    move_cmd->execute(p);
}

TEST(DeserializerTest, DeserializeValidMoveCommandNorthWest) {
    std::string srlzd_cmd = {0x6d /* move */, 0x07 /* north west */};
    std::unique_ptr<Command> cmd = Deserializer::deserialize_command(srlzd_cmd);
    Move* move_cmd = dynamic_cast<Move*>(cmd.get());
    MockPlayer p;
    EXPECT_EQ(move_cmd->get_dir(), Direction::NW);
    EXPECT_CALL(p, move(Direction::NW));
    move_cmd->execute(p);
}

}  // namespace
