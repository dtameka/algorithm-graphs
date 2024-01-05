#ifndef S21_CONTROLLER_H_
#define S21_CONTROLLER_H_

#include "../model/s21_graph.h"
#include "../model/s21_graph_algorithms.h"

namespace s21 {

class Controller {
public:
    Controller() = delete;
    explicit Controller(Graph *graph) : graph_(graph) {}
    Controller(const Controller &other) = delete;
    Controller &operator=(const Controller &other) = delete;
    ~Controller() = default;

    void LoadGraphFromFile(const std::string &filename) {
        try {
            graph_->loadGraphFromFile(filename);
        } catch (...) {
            throw std::runtime_error("Can't load graph from file");
        }
    }

    void exportGraphToDot(const std::string &filename) {
        try {
            graph_->exportGraphToDot(filename);
        } catch (...) {
            throw std::runtime_error("Can't export graph to .dot file");
        }
    }

    auto DepthFirstSearch(std::size_t n) {
        try {
            return GraphAlgorithms::DepthFirstSearch(*graph_, n);
        } catch (...) {
            throw std::runtime_error("Can't find path");
        }
    }

    auto BreadthFirstSearch(std::size_t n) {
        try {
            return GraphAlgorithms::BreadthFirstSearch(*graph_, n);
        } catch (...) {
            throw std::runtime_error("Can't find path");
        }
    }

    auto GetShortestPathBetweenVertices(std::size_t a, std::size_t b) {
        try {
            return GraphAlgorithms::GetShortestPathBetweenVertices(*graph_, a, b);
        } catch (...) {
            throw std::runtime_error("Can't find path");
        }
    }

    auto GetShortestPathsBetweenAllVertices() {
        try {
            return GraphAlgorithms::GetShortestPathsBetweenAllVertices(*graph_);
        } catch (...) {
            throw std::runtime_error("Can't find path");
        }
    }

    auto GetLeastSpanningTree() { 
        try {
            return GraphAlgorithms::GetLeastSpanningTree(*graph_);
        } catch (...) {
            throw std::runtime_error("Can't find path");
        }
    }

    auto SolveTravelingSalesmanProblem() { 
        try {
            return GraphAlgorithms::SolveTravelingSalesmanProblem(*graph_);
        } catch (...) {
            throw std::runtime_error("Can't find path");
        }
    }

private:
    Graph *graph_;
};

} // namespace s21

#endif // S21_CONTROLLER_H_