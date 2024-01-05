#include "s21_graph_algorithms.h"
namespace s21 {
vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph, const int start) {
  if (start >= graph.size() || start < 0) {
    throw std::invalid_argument(
        "[ [Wrong argument] ] :: Graph or start vertex is invalid\n");
  }
  vector<bool> visited(graph.size(), false);
  vector<int> passed_path;
  Stack<int> vertices_stack;

  vertices_stack.push(start);

  while (!vertices_stack.empty()) {
    int vertex = vertices_stack.top();
    vertices_stack.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      passed_path.push_back(vertex + 1);

      for (int neighbor : graph.neighborsFromStack(vertex)) {
        if (!visited[neighbor]) {
          vertices_stack.push(neighbor);
        }
      }
    }
  }
  return passed_path;
}

vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph, int start) {
  if (start >= graph.size() || start < 0) {
    throw std::out_of_range(
        "[ [Wrong argument] ] :: Graph or start vertex is invalid\n");
  }
  vector<bool> visited(graph.size(), false);
  vector<int> passed_path;
  Queue<int> vertices_queue;

  vertices_queue.push(start);

  while (!vertices_queue.empty()) {
    int vertex = vertices_queue.front();
    vertices_queue.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      passed_path.push_back(vertex + 1);

      for (int neighbor : graph.neighborsFromQueue(vertex)) {
        if (!visited[neighbor]) {
          vertices_queue.push(neighbor);
        }
      }
    }
  }
  return passed_path;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  if (vertex1 < 1 || vertex1 > graph.size() || vertex2 < 1 ||
      vertex2 > graph.size()) {
    throw std::invalid_argument(
        "[ [Wrong argument] ] :: Graph or start/end vertex is invalid\n");
  }
  // Счет идет с 0, но пользователь задает с 1, для этого уменьшаем на 1.
  vertex1--;
  vertex2--;

  vector<int> distance(graph.size(), std::numeric_limits<int>::max());
  vector<bool> visited(graph.size(), false);
  Queue<int> vertex_queue;
  distance[vertex1] = 0;
  vertex_queue.push(vertex1);

  while (!vertex_queue.empty()) {
    int process_vertex = vertex_queue.front();
    vertex_queue.pop();

    if (visited.at(process_vertex)) {
      continue;
    }
    visited[process_vertex] = true;

    for (int i = 0; i < graph.size(); ++i) {
      if (graph[process_vertex][i] != 0 && !visited[i]) {
        int new_distance = distance[process_vertex] + graph[process_vertex][i];
        if (new_distance < distance[i]) {
          distance[i] = new_distance;
          vertex_queue.push(i);
        }
      }
    }
  }

  return distance[vertex2];
}

matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  if (graph.size() == 0) {
    throw std::invalid_argument(
        "[ [Wrong argument] ] :: Graph or start vertex is invalid\n");
  }
  auto kinf = std::numeric_limits<int>::max();
  matrix distance(graph.size(), vector<int>(graph.size(), kinf));

  // Инициализация матрицы distance ребрами графа
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph.size(); ++j) {
      if (i == j) {
        distance[i][j] = 0;
      } else if (graph[i][j] != 0) {
        distance[i][j] = graph[i][j];
      }
    }
  }

  // Алгоритм Флойда-Уоршелла
  for (int k = 0; k < graph.size(); ++k) {
    for (int i = 0; i < graph.size(); ++i) {
      for (int j = 0; j < graph.size(); ++j) {
        if (distance[i][k] != kinf && distance[k][j] != kinf &&
            distance[i][k] + distance[k][j] < distance[i][j]) {
          distance[i][j] = distance[i][k] + distance[k][j];
        }
      }
    }
  }

  return distance;
}

matrix GraphAlgorithms::GetLeastSpanningTree(const Graph &graph) {
  int size = graph.size();
  if (size == 0) {
    throw std::invalid_argument("[ [Wrong argument] ] :: Graph is invalid\n");
  }
  vector<bool> visited(size, false);
  vector<int> distances(size, kInf);
  vector<int> parents(size, -1);

  matrix spanning_tree(size, vector<int>(size, 0));

  distances[0] = 0;

  for (int i = 0; i < size - 1; ++i) {
    int min_distance = kInf;
    int min_vertex = -1;

    for (int j = 0; j < size; ++j) {
      if (!visited[j] && distances[j] < min_distance) {
        min_distance = distances[j];
        min_vertex = j;
      }
    }

    visited.at(min_vertex) = true;

    if (parents.at(min_vertex) != -1) {
      spanning_tree[parents[min_vertex]][min_vertex] =
          graph[parents[min_vertex]][min_vertex];
      spanning_tree[min_vertex][parents[min_vertex]] =
          graph[parents[min_vertex]][min_vertex];
    }

    for (int j = 0; j < size; ++j) {
      if (!visited[j] && graph[min_vertex][j] > 0 &&
          graph[min_vertex][j] < distances[j]) {
        parents[j] = min_vertex;
        distances[j] = graph[min_vertex][j];
      }
    }
  }

  return spanning_tree;
}

int GraphAlgorithms::CalculateGraphWeight(const matrix &graph) {
  int weight = 0;
  int size = graph.size();

  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      weight += graph[i][j];
    }
  }

  return weight;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  if (graph.size() == 0) {
    throw std::invalid_argument("[ [Wrong argument] ] :: Graph is invalid\n");
  }
  s21::AntColony ant_colony(graph);
  return ant_colony.SolveSalesmansProblem();
}
}  // namespace s21