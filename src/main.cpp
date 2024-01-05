#include "view/console_view.h"

int main() {
    s21::Graph graph;
    s21::Controller controller(&graph);
    s21::ConsoleView view(&controller);
    view.show();
    return 0;
}