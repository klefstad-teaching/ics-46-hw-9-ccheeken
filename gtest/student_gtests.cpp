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
  EXPECT_TRUE(is_adjacent("kanade", "KaNaDe"));
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

TEST(DijkstrasTests, DijkstraShortestPath) {
  Graph G;
  file_to_graph("./src/small.txt", G);
  vector<int> previous(G.numVertices, -1);
  EXPECT_EQ(dijkstra_shortest_path(G, 0, previous), vector<int>({0, 3, 6, 1}));
  EXPECT_EQ(previous, vector<int>({-1, 3, 1, 0}));
  Graph G2;
  file_to_graph("./src/medium.txt", G2);
  vector<int> previous2(G2.numVertices, -1);
  // EXPECT_EQ(dijkstra_shortest_path(G2, 0, previous2), vector<int>({0, 5, 9, 18, 25, 2}));
  // EXPECT_EQ(previous2, vector<int>({-1, 0, 1, 2, 3, 0}));  // for 1 round of dijkstras
  EXPECT_EQ(dijkstra_shortest_path(G2, 0, previous2), vector<int>({0, 5, 3, 12, 10, 2}));
  EXPECT_EQ(previous2, vector<int>({-1, 0, 5, 2, 5, 0}));
}

TEST(DijkstrasTests, ExtractShortestPath) {
  Graph G;
  file_to_graph("./src/small.txt", G);
  vector<int> previous(G.numVertices, -1);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);
  EXPECT_EQ(extract_shortest_path(distances, previous, 0), vector<int>{0});
  EXPECT_EQ(extract_shortest_path(distances, previous, 3), vector<int>({0, 3}));
  EXPECT_EQ(extract_shortest_path(distances, previous, 2), vector<int>({0, 3, 1, 2}));
}

TEST(DijkstrasTests, PrintPath) {
  Graph G;
  file_to_graph("./src/small.txt", G);
  vector<int> previous(G.numVertices, -1);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);
  vector<int> res = extract_shortest_path(distances, previous, 2);
  print_path(res, 0);
}
