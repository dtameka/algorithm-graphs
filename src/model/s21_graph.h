#ifndef SRC_MODEL_S21_GRAPH_H_
#define SRC_MODEL_S21_GRAPH_H_

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

using std::string;
using std::vector;
using matrix = vector<vector<int>>;
using matrixAntd = vector<vector<double>>;

class Graph {
 public:
  Graph() = default;

  vector<int> operator[](int index);

  const vector<int> operator[](int index) const;

  /**
   * Load a graph from a file.
   *
   * @param filename the name of the file to load the graph from
   *
   * @throws std::runtime_error if the file cannot be opened
   * @throws std::out_of_range if the matrix size is invalid
   */
  void loadGraphFromFile(const string &filename);

  /**
   * Returns a vector of integers representing the neighbors of the given vertex
   * for queue-based algorithms.
   *
   * @param vertex the vertex for which to find neighbors
   *
   * @return a vector of integers representing the neighbors of the given vertex
   *
   * @throws None
   */
  vector<int> neighborsFromQueue(const int &vertex) const;

  /**
   * Returns a vector of integers representing the neighbors of the given vertex
   * for stack-based algorithms.
   *
   * @param vertex the vertex for which to find neighbors
   *
   * @return a vector of integers representing the neighbors of the given vertex
   *
   * @throws None
   */
  vector<int> neighborsFromStack(const int &vertex) const;

  /**
   * Determines if the graph is directed.
   *
   * @return True if the graph is directed, false otherwise.
   */
  bool IsDirected() const;

  /**
   * Exports the graph to a DOT file with the given filename.
   *
   * @param filename the name of the file to export the graph to
   *
   * @throws std::runtime_error if the file could not be created
   */
  void exportGraphToDot(const string &filename) const;

  int size() const;

  /**
   * Prints the elements of the adjacency matrix in a matrix format.
   *
   * @throws None
   */
  void printMatrix() const;

  /**
   * Calculates the weight of the graph.
   *
   * @return The weight of the graph.
   */
  int getGraphWeight();

  int getGraphWeight() const;

 private:
  std::string matrixToDot(bool directed) const;

  bool fileExists(const std::string &filename) const;

  matrix adjacency_matrix_;
};

}  // namespace s21

#endif  // SRC_MODEL_S21_GRAPH_H_