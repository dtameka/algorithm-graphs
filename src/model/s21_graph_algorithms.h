#ifndef SRC_MODEL_S21_GRAPH_ALGORITHMS_H_
#define SRC_MODEL_S21_GRAPH_ALGORITHMS_H_

#include <limits>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "dependencies/s21_queue.h"
#include "dependencies/s21_stack.h"
#include "s21_ant_algorithm.h"
#include "s21_graph.h"

namespace s21 {

class GraphAlgorithms {
 public:
  /**
   * Performs a depth-first search on a given graph starting from a specified
   * vertex.
   *
   * @param graph the graph to perform the depth-first search on
   * @param start the starting vertex for the depth-first search
   *
   * @return a vector of integers representing the path traversed during the
   * depth-first search
   *
   * @throws std::invalid_argument if the start vertex is invalid or graph not
   * found
   */
  static vector<int> DepthFirstSearch(Graph &graph, const int start);

  /**
   * Performs a breadth-first search on the given graph starting from the
   * specified vertex.
   *
   * @param graph the graph to perform the breadth-first search on
   * @param start the starting vertex for the search
   *
   * @return a vector of integers representing the path traversed during the
   * breadth-first search
   *
   * @throws std::out_of_range if the start vertex is invalid or graph not found
   */
  static vector<int> BreadthFirstSearch(Graph &graph, int start);

  /**
   * Calculates the shortest path between two vertices in a graph.
   *
   * @param graph the graph to search for the shortest path
   * @param vertex1 the starting vertex
   * @param vertex2 the ending vertex
   *
   * @return the shortest path between vertex1 and vertex2
   *
   * @throws std::invalid_argument if the graph or start/end vertex is invalid
   */
  static int GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                            int vertex2);

  /**
   * Calculates the shortest paths between all vertices in a given graph using
   * the Floyd-Warshall algorithm.
   *
   * @param graph The graph for which to calculate the shortest paths.
   *
   * @return A matrix representing the shortest distances between each pair of
   * vertices.
   *
   * @throws None.
   */
  static matrix GetShortestPathsBetweenAllVertices(Graph &graph);

  /**
   * GetLeastSpanningTree function calculates the minimum spanning tree of a
   * given graph.
   *
   * @param graph A reference to the graph object.
   *
   * @return A matrix representing the minimum spanning tree.
   *
   * @throws None
   */
  static matrix GetLeastSpanningTree(const Graph &graph);

  /**
   * Calculates the weight of a graph represented by a matrix.
   *
   * @param graph the matrix representing the graph
   *
   * @return the weight of the graph
   *
   * @throws None
   */
  static int CalculateGraphWeight(const matrix &graph);

  /**
   * Solve the Traveling Salesman Problem using the Ant Colony algorithm.
   *
   * @param graph the graph representing the cities and distances
   *
   * @return the optimal solution to the Traveling Salesman Problem
   *
   * @struct TsmResult
   * @field distance the total distance of the optimal solution
   * @field path the optimal path
   *
   */
  static TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};

}  // namespace s21

#endif  // SRC_MODEL_S21_GRAPH_ALGORITHMS_H_
