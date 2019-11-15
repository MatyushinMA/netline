#ifndef NETLINE_GRAPH_LINE_GRAPH_H
#define NETLINE_GRAPH_LINE_GRAPH_H

#include <netline/graph/node.h>

#include <vector>
#include <cassert>
#include <string>
#include <unordered_map>
#include <set>

namespace Netline::Graph {

class LineGraph {
private:
    std::vector<Node> nodes;
    std::vector<std::int64_t> acquired_potential;
    std::unordered_map<std::string, std::size_t> id_map;
    std::set<std::size_t> inputs;
    std::set<std::size_t> outputs;

    void clear_buffers() {
        for (std::size_t i = 0; i < acquired_potential.size(); i++) {
            acquired_potential[i] = 0;
        }
    }

public:
    LineGraph() {}

    /**
    Adds new empty node
    */
    void add_node(std::string id="", NodeType type=Excitatory);

    /**
    Sets node as input
    */
    void set_input(std::string id);

    /**
    Sets node as output
    */
    void set_output(std::string id);

    /**
    Adds edge from from to to
    */
    void add_edge(std::size_t from, std::size_t to);
    void add_edge(std::string from_id, std::size_t to);
    void add_edge(std::size_t from, std::string to_id);
    void add_edge(std::string from_id, std::string to_id);

    /**
    Sets values of input potentials
    */
    void feed(std::unordered_map<std::string, double> in_values);

    /**
    Moves potentials through graph for i steps
    */
    std::unordered_map<std::string, double> step(std::size_t num_steps=1, std::size_t global_step=0, bool* has_activated_nodes=nullptr);

    /**
    Moves potentials through graph until no activations left except for outputs
    */
    std::unordered_map<std::string, double> evaluate();

    /**
    Removes edge
    */
    void remove_edge(std::size_t from, std::size_t to);
    void remove_edge(std::string from_id, std::size_t to);
    void remove_edge(std::size_t from, std::string to_id);
    void remove_edge(std::string from_id, std::string to_id);

    friend std::ostream& operator<<(std::ostream &stream, const LineGraph& g);
};

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_LINE_GRAPH_H
