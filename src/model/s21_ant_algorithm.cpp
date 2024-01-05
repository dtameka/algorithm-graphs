#include "s21_ant_algorithm.h"

namespace s21 {

AntColony::AntColony(const Graph &graph)
    : graph_(graph), kQ_(0.015 * graph.getGraphWeight()) {
  const int kVertexesCount = graph_.size();
  matrixAntd matrix(kVertexesCount, std::vector<double>(kVertexesCount));
  for (int row = 0; row != kVertexesCount; ++row)
    for (int col = 0; col != kVertexesCount; ++col)
      if (row != col) matrix[row][col] = kPheromone0_;

  pheromone_ = std::move(matrix);
}

/**
 * Create ants for the ant colony.
 *
 */
void AntColony::CreateAnts() {
  const auto kAntsCount = graph_.size();
  ants_.resize(kAntsCount);

  for (std::size_t i = 0, size = ants_.size(); i != size; ++i)
    ants_[i] = Ant(i);
}

/**
 * Updates the global pheromone matrix based on the local pheromone update
 * matrix.
 *
 * @param lpu the local pheromone update matrix
 *
 * @throws None
 */
void AntColony::UpdateGlobalPheromone(const matrixAntd &lpu) {
  for (std::size_t i = 0, size = lpu.size(); i != size; ++i) {
    for (std::size_t j = 0; j != size; ++j) {
      pheromone_[i][j] = (1 - kInitialPheromone) * pheromone_[i][j] + lpu[i][j];
      if (pheromone_[i][j] < 0.01 and i != j) pheromone_[i][j] = 0.01;
    }
  }
}

/**
 * Generates a random number between 0.0 and 1.0 using a uniform distribution.
 *
 * @return The generated random number.
 */
double Ant::getRandomChoice() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  return dis(gen);
}

/**
 * Returns a vector of integers representing the neighboring vertices of the
 * Ant's current location in the given Graph.
 *
 * @param graph The Graph object representing the graph structure.
 *
 * @return A vector of integers representing the neighboring vertices.
 *
 */
std::vector<int> Ant::getNeighborVertexes(const Graph &graph) {
  std::vector<int> vertexes;
  for (int i = 0; i != graph.size(); ++i) {
    bool edge_is_exist = graph[current_location][i] != 0;
    bool vertex_is_unvisited =
        std::find(visited.begin(), visited.end(), i) == visited.end();
    if (edge_is_exist && vertex_is_unvisited) vertexes.push_back(i);
  }
  return vertexes;
}

/**
 * Makes a choice for the Ant based on the given parameters.
 *
 * @param graph The graph representing the environment.
 * @param phero_lvl The pheromone level matrix.
 *
 */
void Ant::MakeChoice(const Graph &graph, const matrixAntd &phero_lvl) {
  if (ant_result.path.empty()) {
    ant_result.path.push_back(current_location);
    visited.push_back(current_location);
  }

  std::vector<int> neighbor_vertexes = getNeighborVertexes(graph);

  if (neighbor_vertexes.empty()) {
    can_continue = false;
    if (graph[current_location][start_location] != 0) {
      ant_result.path.push_back(start_location);
      ant_result.distance += graph[current_location][start_location];
    }
    return;
  }

  std::vector<double> choosing_probability(neighbor_vertexes.size());

  std::vector<double> wish;
  std::vector<double> probability;
  double sum = 0.0f;
  for (auto const &it : neighbor_vertexes) {
    double pheromone_level = phero_lvl[current_location][it];
    double heuristic = graph[current_location][it];
    double eta = 1.0 / heuristic;
    wish.push_back(std::pow(pheromone_level, kAlpha_) * std::pow(eta, kBeta_));
    sum += wish.back();
  }

  for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size();
       ++neighbor) {
    probability.push_back(wish[neighbor] / sum);
    if (neighbor == 0)
      choosing_probability[neighbor] = probability.back();
    else
      choosing_probability[neighbor] =
          choosing_probability[neighbor - 1] + probability.back();
  }

  std::size_t next_vertex = 0;
  double choose = getRandomChoice();

  // Можно сделать бинарный поиск

  for (std::size_t n = 0; n != neighbor_vertexes.size(); ++n) {
    if (choose <= choosing_probability[n]) {
      next_vertex = neighbor_vertexes[n];
      break;
    }
  }

  ant_result.path.push_back(next_vertex);
  ant_result.distance += graph[current_location][next_vertex];
  visited.push_back(next_vertex);
  current_location = next_vertex;
}

TsmResult AntColony::SolveSalesmansProblem() {
  if (graph_.size() == 0) return {};

  const std::size_t kVertexesCount = graph_.size();
  std::size_t counter = 0;

  TsmResult path;
  path.distance = std::numeric_limits<double>::max();

  while (counter++ != kNumIterations) {
    matrixAntd local_pheromone_update(kVertexesCount,
                                      std::vector<double>(kVertexesCount, 0.0));
    CreateAnts();

    for (auto &ant : ants_) {
      while (ant.can_continue) ant.MakeChoice(graph_, pheromone_);

      auto ant_path = ant.ant_result;
      if (ant_path.path.size() == kVertexesCount + 1) {
        if (path.distance > ant.ant_result.distance) {
          path = std::move(ant.ant_result);
          counter = 0;
        }

        for (std::size_t v = 0; v != ant_path.path.size() - 1; ++v)
          local_pheromone_update[ant_path.path[v]][ant_path.path[v + 1]] +=
              kQ_ / ant_path.distance;
      }
    }
    UpdateGlobalPheromone(local_pheromone_update);
  }
  return path;
}

}  // namespace s21