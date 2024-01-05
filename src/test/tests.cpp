#include "tests.h"
namespace s21 {
TEST(LoadGraph, ValidGraphFile) {
  std::string filename = "test/graphs/valid_graph.txt";

  ASSERT_NO_THROW(graph.loadGraphFromFile(filename));
}

TEST(LoadGraph, InvalidMatrixSize) {
  std::string filename = "test/graphs/invalid_matrix_size.txt";

  ASSERT_THROW(graph.loadGraphFromFile(filename), std::out_of_range);
}

TEST(LoadGraph, EmptyGraphFile) {
  std::string filename = "test/graphs/empty_graph.txt";

  ASSERT_THROW(graph.loadGraphFromFile(filename), std::out_of_range);
}

TEST(LoadGraph, GraphFileWithNegativeValues) {
  std::string filename = "test/graphs/graph_with_negative_values.txt";

  ASSERT_THROW(graph.loadGraphFromFile(filename), std::out_of_range);
}

TEST(LoadGraph, InvalidMatrixSize2) {
  std::string filename = "test/graphs/invalid_matrix_size2.txt";

  ASSERT_THROW(graph.loadGraphFromFile(filename), std::out_of_range);
}

TEST(LoadGraph, InvalidMatrixSize3) {
  std::string filename = "test/graphs/invalid_matrix_size3.txt";

  ASSERT_THROW(graph.loadGraphFromFile(filename), std::out_of_range);
}

TEST(LoadGraph, ExportDot) {
  std::string filename = "test/graphs/valid_graph.txt";

  ASSERT_NO_THROW(graph.loadGraphFromFile(filename));
  ASSERT_NO_THROW(graph.exportGraphToDot("test/RESULT_valid_graph.dot"));
}
TEST(loadGraphFromFile, WeightedDirectedGraph) {
  graph.loadGraphFromFile("test/graphs/valid_graph.txt");
  std::vector<std::vector<int>> excepted = {{0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
                                  {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
                                  {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
                                  {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
                                  {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
                                  {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
                                  {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
                                  {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
                                  {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
                                  {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
                                  {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};
  for (unsigned i = 0; i < excepted.size(); ++i)
    for (unsigned j = 0; j < excepted[i].size(); ++j) {
      EXPECT_EQ(excepted[i][j], graph[i][j]);
    }
}

TEST(stack, operations2) {
  s21::Stack<int> a{3, 4, 5};
  a.top();
  a.pop();
  a.size();
  a.empty();
}

TEST(stack, operations3) {
  s21::Stack<int> a{3, 4, 5};
  s21::Stack<int> b{2, 6, 8};
  s21::Stack<int> c(a);
  s21::Stack<int> d(b);
  c.swap(b);
  d.swap(a);
  ASSERT_EQ(c.top(), 8);
  ASSERT_EQ(d.top(), 5);
  c.top();
  auto it = c.top();
}

TEST(queue, create) {
  s21::Queue<int> a;
  s21::Queue<int> b({1, 2, 3, 4});
  s21::Queue<int> c(b);
  s21::Queue<int> d;
  d = c;
  s21::Queue<int> e = s21::Queue<int>({1, 3, -5});
  a = s21::Queue<int>(b);
}

TEST(queue, operations) {
  s21::Queue<int> a;
  a.empty();

  a.back();
  a.size();
  a.front();
}

TEST(queue, operations2) {
  s21::Queue<int> a;
  a.push(3);
  a.push(4);
  a.push(5);
  a.pop();
  a.back();
  a.front();
}

TEST(queue, operations3) {
  s21::Queue<int> a{3, 4, 5};
  s21::Queue<int> b{2, 6, 8};
  s21::Queue<int> c(a);
  s21::Queue<int> d(b);
  c.swap(b);
  d.swap(a);
  ASSERT_EQ(c.back(), 8);
  ASSERT_EQ(d.back(), 5);
}

TEST(DepthFirstSearchTest, udg2) {
  graph.loadGraphFromFile("test/graphs/valid_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
}

TEST(DepthFirstSearchTest, dg1) {
  graph.loadGraphFromFile("test/graphs/unweighted_directed_graph.txt");
  vector<int> expected = {1, 2, 4, 5, 3};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(DepthFirstSearchTest, uug1) {
  graph.loadGraphFromFile(
      "test/graphs/unweighted_undirected_graph.txt");
  vector<int> expected = {1, 2, 4, 3, 5, 6};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(graph, 0);
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(DepthFirstSearchTest, wug1) {
  graph.loadGraphFromFile("test/graphs/valid_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::DepthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(BreadthFirstSearch, udg2) {
  graph.loadGraphFromFile("test/graphs/valid_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(BreadthFirstSearch, dg1) {
  graph.loadGraphFromFile("test/graphs/unweighted_directed_graph.txt");
  vector<int> expected = {1, 2, 4, 5, 3};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(BreadthFirstSearch, uug1) {
  graph.loadGraphFromFile(
      "test/graphs/unweighted_undirected_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(BreadthFirstSearch, wug1) {
  graph.loadGraphFromFile("test/graphs/valid_graph.txt");
  vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  vector<int> actual = GraphAlgorithms::BreadthFirstSearch(graph, 0);
  ASSERT_EQ(expected.size(), actual.size());
  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], actual[i]);
  }
}

TEST(GetShortestPathBetweenVertices, UnweightedDirectedGraph) {
  graph.loadGraphFromFile("test/graphs/unweighted_directed_graph.txt");

  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 3), 3);
}

TEST(GetShortestPathBetweenVertices, dwg) {
  graph.loadGraphFromFile("test/graphs/dwg.txt");
  EXPECT_EQ(GraphAlgorithms::GetShortestPathBetweenVertices(graph, 1, 4), 2);
}

TEST(GetShortestPathsBetweenAllVertices, udg1) {
  ASSERT_NO_THROW(graph.loadGraphFromFile("test/graphs/unweighted_directed_graph.txt"));

  vector<vector<int>> expected = {{0, 1, 3, 1, 2},
                                  {2, 0, 3, 1, 2},
                                  {1, 2, 0, 1, 1},
                                  {1, 2, 2, 0, 1},
                                  {1, 2, 1, 2, 0}};

  vector<vector<int>> actual =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);

  ASSERT_EQ(expected, actual);
}

TEST(GetLeastSpanningTree, validGraph) {
  graph.loadGraphFromFile("test/graphs/ost.txt");
  vector<vector<int>> res = GraphAlgorithms::GetLeastSpanningTree(graph);

  EXPECT_EQ(GraphAlgorithms::CalculateGraphWeight(res), 49);
}

// TEST(SolveTravelingSalesmanProblem, WeightedUndirectedGraph) {
//   s21::TsmResult result;
//   graph.loadGraphFromFile("test/graphs/valid_graph.txt");
//   result = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
//   EXPECT_LE(result.distance, 255);
// }

TEST(SolveTravelingSalesmanProblem, wug2) {
  s21::TsmResult result;
  graph.loadGraphFromFile("test/graphs/wug2.txt");
  result = GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
  s21::TsmResult expected = {{1, 3, 4, 2, 1}, 80};
  EXPECT_EQ(result.distance, expected.distance);
}

} // namespace s21

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
