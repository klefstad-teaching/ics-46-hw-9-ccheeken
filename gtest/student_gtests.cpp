#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(LadderTests, EditDistanceWithin) {                       // distance
  EXPECT_TRUE(edit_distance_within("sitting", "kitten", 4));  // 3
  EXPECT_TRUE(edit_distance_within("Sunday", "Saturday", 4)); // 3
  EXPECT_TRUE(edit_distance_within("mafuyu", "mizuki", 5));   // 4
  EXPECT_FALSE(edit_distance_within("kanade", "canada", 2));  // 2
  EXPECT_FALSE(edit_distance_within("ena", "enanan", 3));     // 3
}

TEST(LadderTests, IsAdjacent) {
  EXPECT_TRUE(is_adjacent("hi", "hii"));
  EXPECT_FALSE(is_adjacent("hi", "hey"));
  EXPECT_TRUE(is_adjacent("car", "cat"));
  EXPECT_TRUE(is_adjacent("cat", "chat"));
  EXPECT_TRUE(is_adjacent("chat", "cheat"));
  EXPECT_FALSE(is_adjacent("mafuyu", "yuki"));
}

TEST(LadderTests, GenerateWordLadder) {
  // ah
}
