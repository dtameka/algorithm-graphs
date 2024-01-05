#ifndef S21_CONSOLE_VIEW_H_
#define S21_CONSOLE_VIEW_H_

#include <cstdio>

#include "../controller/controller.h"

namespace s21 {

class ConsoleView {
 public:
  explicit ConsoleView(Controller *controller) : controller_(controller) {}
  ~ConsoleView() {}

  void show() {
    while (run) {
      DisplayMenu();
      std::string path;
      std::string choice;
      std::string vertex;
      std::string end_vertex;
      std::string start_vertex;
      std::cin >> choice;
      if (choice.length() != 1 || !std::isdigit(choice[0])) {
        InvalidChoice();
        continue;
      }
      char res = choice[0];
      std::cout << std::endl;
      switch (res) {
        case '1':
          std::cout << "Enter the path to the file: ";

          std::cin >> path;
          std::cout << std::endl;
          try {
            controller_->LoadGraphFromFile(path);
          } catch (...) {
            ErrorHandler();
            break;
          }
          std::cout << "Graph loaded successfully" << std::endl;
          std::cout << "Press any key to continue...";
          std::cin.ignore();
          std::getchar();
          path.clear();
          break;
        case '2':
          std::cout << "Enter the starting vertex: ";
          std::cin >> vertex;
          std::cout << std::endl;
          try {
            if (isDigits(vertex)) {
              result_vector_ = controller_->DepthFirstSearch(std::stoi(vertex));
            } else {
              throw "";
            }
          } catch (...) {
            ErrorHandler();
            break;
          }
          DisplayResultBreadth(result_vector_);
          break;
        case '3':
          std::cout << "Enter the starting vertex: ";
          std::cin >> vertex;
          std::cout << std::endl;
          try {
            if (isDigits(vertex)) {
              result_vector_ =
                  controller_->BreadthFirstSearch(std::stoi(vertex));
            } else {
              throw "";
            }
          } catch (...) {
            ErrorHandler();
            break;
          }
          DisplayResultDepth(result_vector_);
          break;
        case '4':
          std::cout << "Enter the start vertex: ";
          std::cin >> start_vertex;
          std::cout << std::endl;

          std::cout << "Enter the end vertex: ";
          std::cin >> end_vertex;
          std::cout << std::endl;
          try {
            if (isDigits(start_vertex) && isDigits(end_vertex)) {
              result_int_ = controller_->GetShortestPathBetweenVertices(
                  std::stoi(start_vertex), std::stoi(end_vertex));
            } else {
              throw "";
            }
          } catch (...) {
            ErrorHandler();
            break;
          }
          DisplayResultShortestPath(result_int_);
          break;
        case '5':
          try {
            result_matrix_ = controller_->GetShortestPathsBetweenAllVertices();
          } catch (...) {
            ErrorHandler();
            break;
          }
          DisplayResultShortestPathsAllVert(result_matrix_);
          break;
        case '6':
          try {
            result_matrix_ = controller_->GetLeastSpanningTree();
          } catch (...) {
            ErrorHandler();
            std::getchar();
            break;
          }
          DisplayResultLeastSpanningTree(result_matrix_);
          break;
        case '7':
          try {
            result_tsm_ = controller_->SolveTravelingSalesmanProblem();
          } catch (...) {
            ErrorHandler();
            break;
          }
          DisplayResultSalesmanProblem(result_tsm_);
          break;
        case '0':
          run = false;
          break;
        default:
          InvalidChoice();
          break;
      }
    }
  }

  void ErrorHandler() const {
    std::cout << "Error. Try again." << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  void InvalidChoice() const {
    std::cout << "Invalid choice. Please try again." << std::endl;
    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  bool isDigits(std::string str) {
    bool is_all_digits = true;
    for (auto const &it : str) {
      if (!std::isdigit(it)) {
        is_all_digits = false;
      }
    }
    return is_all_digits;
  }

 private:
  void DisplayMenu() const {
    std::system("clear");
    std::cout << "\\=========================================================================/" << std::endl;
    std::cout << "|                                   M E N U                               |" << std::endl;
    std::cout << "|=========================================================================|" << std::endl;
    std::cout << "|         1. Load the original graph from a file                          |" << std::endl;
    std::cout << "|         2. Graph traversal in breadth                                   |" << std::endl;
    std::cout << "|         3. Graph traversal in depth                                     |" << std::endl;
    std::cout << "|         4. Search for the shortest path between two vertices            |" << std::endl;
    std::cout << "|         5. Search for the shortest paths between all pairs of vertices  |" << std::endl;
    std::cout << "|         6. Search for the minimal spanning tree in the graph            |" << std::endl;
    std::cout << "|         7. Solve the salesman problem                                   |" << std::endl;
    std::cout << "|         0. Quit                                                         |" << std::endl;
    std::cout << "/=========================================================================\\" << std::endl;
    std::cout << "Enter your choice: ";
  }

  void DisplayResultBreadth(std::vector<int> result) const {
    std::cout << "Breadth-first search result: [";
    std::string str = "";
    for (auto const &it : result) {
      str += std::to_string(it) + ", ";
    }
    str.resize(str.size() - 2);
    str += "]";
    std::cout << str << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  void DisplayResultDepth(std::vector<int> result) const {
    std::cout << "Depth-first search result: [";
    std::string str = "";
    for (auto const &it : result) {
      str += std::to_string(it) + ", ";
    }
    str.resize(str.size() - 2);
    str += "]";
    std::cout << str << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  void DisplayResultShortestPath(int result) const {
    std::cout << "Shortest path result: " << result << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  void DisplayResultShortestPathsAllVert(
      std::vector<vector<int>> result) const {
    std::cout << "Shortest paths result: " << std::endl;
    std::string str = "";
    int i = 1;
    for (auto const &it : result) {
      str += std::to_string(i++) + " -- [";
      for (auto const &it2 : it) {
        str += std::to_string(it2) + ", ";
      }
      str.resize(str.size() - 2);
      str += "]\n";
    }
    str.resize(str.size() - 1);
    std::cout << str << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  void DisplayResultLeastSpanningTree(
      const std::vector<std::vector<int>> &result) const {
    std::cout << "Least spanning tree result: " << std::endl;
    std::string str = "";
    int i = 1;
    for (auto const &it : result) {
      str += std::to_string(i++) + " -- [";
      for (auto const &it2 : it) {
        str += std::to_string(it2) + ", ";
      }
      str.resize(str.size() - 2);
      str += "]\n";
    }
    str.resize(str.size() - 1);
    std::cout << str << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  void DisplayResultSalesmanProblem(TsmResult result) const {
    std::cout << "Salesman problem result: " << std::endl;
    std::cout << "Distance: " << result.distance << std::endl;
    std::cout << "Path: [";
    std::string str;
    for (auto const &it : result.path) {
      str += std::to_string(it) + ", ";
    }
    str.resize(str.size() - 2);
    str += "]";
    std::cout << str << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::getchar();
  }

  Controller *controller_;

  bool run = true;
  std::vector<int> result_vector_;
  std::vector<vector<int>> result_matrix_;
  int result_int_;
  TsmResult result_tsm_;
};

}  // namespace s21

#endif  // SRC_VIEW_CONSOLE_VIEW_H_
