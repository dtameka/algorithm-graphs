#include "s21_graph.h"
namespace s21 {

vector<int> Graph::operator[](int index) { return adjacency_matrix_[index]; }

const vector<int> Graph::operator[](int index) const {
  return adjacency_matrix_[index];
}

void Graph::loadGraphFromFile(const string &filename) {
  if (!adjacency_matrix_.empty()) {
    adjacency_matrix_.clear();
  }
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("[ [Wrong argument] ] :: File not found\n");
  }

  string tmp_str;
  int vert_count = 0;
  std::getline(file, tmp_str);
  if (sscanf(tmp_str.c_str(), "%d", &vert_count) != 1 || vert_count < 1) {
    throw std::out_of_range("[ [File error] ] :: Matrix size must be > 0\n");
  }

  int stream_int;
  while (std::getline(file, tmp_str)) {
    std::stringstream stream(tmp_str);
    vector<int> tmp_vector;
    while (stream >> stream_int) {
      tmp_vector.push_back(stream_int);
    }
    adjacency_matrix_.push_back(tmp_vector);
  }

  if (adjacency_matrix_.size() != vert_count) {
    throw std::out_of_range("[ [File error] ] :: Invalid matrix size\n");
  }

  for (int i = 0; i < vert_count; ++i) {
    if (adjacency_matrix_[i].size() != vert_count ||
        adjacency_matrix_[i][0] < 0) {
      throw std::out_of_range("[ [File error] ] :: Invalid matrix size\n");
    }
  }
  for (auto const &it : adjacency_matrix_) {
    for (auto const &it2 : it) {
      if (it2 < 0) {
        throw std::out_of_range(
            "[ [File error] ] :: Negative matrix element\n");
      }
    }
  }
}

vector<int> Graph::neighborsFromQueue(const int &vertex) const {
  vector<int> result;
  for (int i = 0; i < size(); ++i) {
    if (adjacency_matrix_.at(vertex).at(i) > 0) {
      result.push_back(i);
    }
  }
  return result;
}

vector<int> Graph::neighborsFromStack(const int &vertex) const {
  vector<int> result;
  for (int i = size() - 1; i >= 0; --i) {
    if (adjacency_matrix_.at(vertex).at(i) > 0) {
      result.push_back(i);
    }
  }
  return result;
}

bool Graph::IsDirected() const {
  for (int i = 0; i < size(); ++i) {
    for (int j = i + 1; j < size(); ++j) {
      if (adjacency_matrix_.at(i).at(j) != adjacency_matrix_.at(j).at(i)) {
        return true;
      }
    }
  }
  return false;
}

void Graph::exportGraphToDot(const string &filename) const {
  if (fileExists(filename)) {
    std::remove(filename.c_str());
  }

  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("[ [Wrong argument] ] :: File was not created\n");
  }
  std::string dot_graph = matrixToDot(IsDirected());
  file << dot_graph;
  file.close();

  std::cout << "File \"" << filename << "\" was successfully created"
            << std::endl;
}

int Graph::getGraphWeight() {
  int weight = 0;
  int size = adjacency_matrix_.size();

  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      weight += adjacency_matrix_[i][j];
    }
  }

  return weight;
}

int Graph::getGraphWeight() const {
  return const_cast<Graph *>(this)->getGraphWeight();
}

std::string Graph::matrixToDot(bool directed) const {
  std::string dot_graph;

  dot_graph += directed ? "digraph MyGraph" : "graph MyGraph";

  dot_graph += " {";

  for (int i = 0; i < adjacency_matrix_.size(); ++i) {
    for (int j = 0; j < adjacency_matrix_[i].size(); ++j) {
      if (adjacency_matrix_[i][j] > 0) {
        dot_graph += "\n  " + std::to_string(i) + (directed ? " -> " : " -- ") +
                     std::to_string(j) +
                     " [label=" + std::to_string(adjacency_matrix_[i][j]) +
                     "];";
      }
    }
  }
  dot_graph += "\n}";

  return dot_graph;
}

bool Graph::fileExists(const std::string &filename) const {
  std::ifstream file(filename);
  return file.good();
}

int Graph::size() const { return static_cast<int>(adjacency_matrix_.size()); }
}  // namespace s21