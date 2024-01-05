#ifndef SRC_MODEL_S21_ANT_ALGORITHM_H_
#define SRC_MODEL_S21_ANT_ALGORITHM_H_

#include <limits>
#include <vector>

#include "s21_graph.h"

namespace s21 {

const double kAlpha_ = 1.0;
const double kBeta_ = 2.0;

const int kInf = std::numeric_limits<int>::max();

struct TsmResult {
  std::vector<int> path;
  double distance;
};

struct Ant {
  explicit Ant(int start_vertex = 0)
      : start_location(start_vertex), current_location(start_vertex){};
  void MakeChoice(const Graph &graph, const matrixAntd &phero_lvl);
  double getRandomChoice();
  std::vector<int> getNeighborVertexes(const Graph &graph);

  bool can_continue = true;
  std::vector<int> visited;
  TsmResult ant_result;
  double quantity = 0;
  int start_location = 0, current_location = 0;
};

class AntColony {
 public:
  explicit AntColony(const Graph &graph);

  TsmResult SolveSalesmansProblem();

 private:
  const int kNumAnts = 100;
  const int kNumIterations = 2000;
  const double kPheromone0_ = 1;
  const double kQ_ = 100.0;
  const double kInitialPheromone = 0.1;

  void CreateAnts();
  void UpdateGlobalPheromone(const matrixAntd &local_pheromone_update);

  Graph graph_;
  std::vector<Ant> ants_;
  matrixAntd pheromone_;
};

}  // namespace s21
#endif  // SRC_MODEL_S21_ANT_ALGORITHM_H_