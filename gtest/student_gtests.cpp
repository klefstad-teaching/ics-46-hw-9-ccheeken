#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(LadderTests, EditDistanceWithin) {
  EXPECT_TRUE(edit_distance_within("sitting", "kitten", 3));
  EXPECT_TRUE(edit_distance_within("Sunday", "Saturday", 3));
  EXPECT_TRUE(edit_distance_within("mafuyu", "mizuki", 4));
  EXPECT_TRUE(edit_distance_within("kanade", "canada", 2));
  EXPECT_TRUE(edit_distance_within("ena", "enanan", 3));
  EXPECT_FALSE(edit_distance_within("mizuki", "amia", 1));
}

TEST(LadderTests, IsAdjacent) {
  EXPECT_TRUE(is_adjacent("hi", "hii"));
  EXPECT_FALSE(is_adjacent("hi", "hey"));
  EXPECT_TRUE(is_adjacent("car", "cat"));
  EXPECT_TRUE(is_adjacent("cat", "chat"));
  EXPECT_TRUE(is_adjacent("chat", "cheat"));
  EXPECT_FALSE(is_adjacent("kanade", "KaNaDe"));
  EXPECT_FALSE(is_adjacent("mafuyu", "yuki"));
}

TEST(LadderTests, LoadWords) {
  set<string> s;
  load_words(s, "./src/words.txt");
  EXPECT_NE(s.find("Aarhus"), s.end());
  EXPECT_NE(s.find("leaf"), s.end());
  EXPECT_NE(s.find("Zurich"), s.end());
  EXPECT_EQ(s.find("asjfklsdh"), s.end());
}

TEST(LadderTests, GenerateWordLadder) {
  set<string> s;
  load_words(s, "./src/words.txt");
  EXPECT_EQ(generate_word_ladder("piss", "poop", s), vector<string>({}));
  EXPECT_EQ(generate_word_ladder("wonderhoy", "wonderhoy", s), vector<string>({}));
  EXPECT_EQ(generate_word_ladder("peek", "peeks", s), vector<string>({"peek", "peeks"}));
}

TEST(LadderTests, PrintWordLadder) {
  set<string> s;
  load_words(s, "./src/words.txt");
  print_word_ladder(generate_word_ladder("cat", "dog", s));
}

