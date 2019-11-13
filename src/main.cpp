#include <iostream>
#include <netline/graph/line_graph.h>

int main() {
    using namespace Netline::Graph;
    LineGraph graph = LineGraph();
    graph.add_node("in");
    graph.add_node("out");
    graph.add_node("step", NodeType::Inhibitory);
    graph.add_edge("in", "step");
    graph.add_edge("step", "out");
    graph.add_edge("step", "in");
    graph.add_edge("in", "out");
    graph.add_edge("out", "in");
    graph.set_input("in");
    graph.set_output("out");
    graph.feed({{"in", 850}});
    auto ret = graph.evaluate();
    for (auto [identifier, potential] : ret) {
        std::cout << identifier << " : " << potential << std::endl;
    }
    return 0;
}
