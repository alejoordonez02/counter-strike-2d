#include "server/game/world/equipment/bomb.h"

#include "gtest/gtest.h"

namespace {
TEST(BombTest, BombCanBePlanted) {
    Bomb bomb(Position(0, 0), 30);
    bomb.plant();
    EXPECT_TRUE(bomb.is_planted());
}

TEST(BombTest, BombExplodesWhenTimerIsDone) {
    Bomb bomb(Position(0, 0), 30);
    bomb.plant();
    bomb.update(30);
    EXPECT_TRUE(bomb.has_exploded());
}

TEST(BombTest, BombDoesNotExplodeIfNotPlanted) {
    Bomb bomb(Position(0, 0), 30);
    bomb.update(30);
    EXPECT_FALSE(bomb.has_exploded());
}

TEST(BombTest, BombExplodesWhenTimerIsDoneWithMoreThanOneUpdate) {
    Bomb bomb(Position(0, 0), 30);
    bomb.update(15);
    bomb.update(15);
    EXPECT_FALSE(bomb.has_exploded());
}

TEST(BombTest, BombDoesNotExplodeIfTimerIsNotDone) {
    Bomb bomb(Position(0, 0), 30);
    bomb.update(15);
    EXPECT_FALSE(bomb.has_exploded());
}

TEST(BombTest, BombDoesNotExplodeIfTimerIsNotDoneWithMoreThanOneUpdate) {
    Bomb bomb(Position(0, 0), 30);
    bomb.update(10);
    bomb.update(10);
    EXPECT_FALSE(bomb.has_exploded());
}

TEST(BombTest, BombCanBeDefused) {
    Bomb bomb(Position(0, 0), 30);
    bomb.plant();
    bomb.defuse();
    EXPECT_TRUE(bomb.is_defused());
}

TEST(BombTest, BombCanNotBeDefusedIfItWasNotPlanted) {
    Bomb bomb(Position(0, 0), 30);
    bomb.defuse();
    EXPECT_FALSE(bomb.is_defused());
}

TEST(BombTest, BombDoesNotExplodeIfDefused) {
    Bomb bomb(Position(0, 0), 30);
    bomb.plant();
    bomb.defuse();
    bomb.update(30);
    EXPECT_FALSE(bomb.has_exploded());
}

TEST(BombTest, BombStillHasExplodedIfDefusedAfterExplotion) {
    Bomb bomb(Position(0, 0), 30);
    bomb.plant();
    bomb.update(30);
    bomb.defuse();
    EXPECT_TRUE(bomb.has_exploded());
}

}  // namespace
