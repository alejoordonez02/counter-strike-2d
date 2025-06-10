#include "server/model/bomb.h"

#include "gtest/gtest.h"

namespace {
TEST(BombTest, BombCanBePlanted) {
    Bomb bomb(30);
    bomb.plant();
    EXPECT_EQ(bomb.is_planted(), true);
}

TEST(BombTest, BombExplodesWhenTimerIsDone) {
    Bomb bomb(30);
    bomb.plant();
    bomb.update(30);
    EXPECT_EQ(bomb.has_exploded(), true);
}

TEST(BombTest, BombDoesNotExplodeIfNotPlanted) {
    Bomb bomb(30);
    bomb.update(30);
    EXPECT_EQ(bomb.has_exploded(), false);
}

TEST(BombTest, BombExplodesWhenTimerIsDoneWithMoreThanOneUpdate) {
    Bomb bomb(30);
    bomb.update(15);
    bomb.update(15);
    EXPECT_EQ(bomb.has_exploded(), false);
}

TEST(BombTest, BombDoesNotExplodeIfTimerIsNotDone) {
    Bomb bomb(30);
    bomb.update(15);
    EXPECT_EQ(bomb.has_exploded(), false);
}

TEST(BombTest, BombDoesNotExplodeIfTimerIsNotDoneWithMoreThanOneUpdate) {
    Bomb bomb(30);
    bomb.update(10);
    bomb.update(10);
    EXPECT_EQ(bomb.has_exploded(), false);
}

TEST(BombTest, BombCanBeDefused) {
    Bomb bomb(30);
    bomb.plant();
    bomb.defuse();
    EXPECT_EQ(bomb.is_defused(), true);
}

TEST(BombTest, BombCanNotBeDefusedIfItWasNotPlanted) {
    Bomb bomb(30);
    bomb.defuse();
    EXPECT_EQ(bomb.is_defused(), false);
}

TEST(BombTest, BombDoesNotExplodeIfDefused) {
    Bomb bomb(30);
    bomb.plant();
    bomb.defuse();
    bomb.update(30);
    EXPECT_EQ(bomb.has_exploded(), false);
}

TEST(BombTest, BombStillHasExplodedIfDefusedAfterExplotion) {
    Bomb bomb(30);
    bomb.plant();
    bomb.update(30);
    bomb.defuse();
    EXPECT_EQ(bomb.has_exploded(), true);
}

}  // namespace
