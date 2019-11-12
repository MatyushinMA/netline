#include <iostream>
#include <netline/graph/line_graph.h>

int main() {
    using namespace Netline;
    Graph::LineGraph graph = Graph::LineGraph();
    graph.add_node("in");
    graph.add_node("out");
    graph.add_edge("in", "out");
    graph.add_edge("out", "in");
    graph.set_input("in");
    graph.set_output("out");
    graph.initialize({{"in", 850}});
    graph.print();
    graph.step();
    graph.print();
    return 0;
}
