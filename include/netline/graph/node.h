#ifndef NETLINE_GRAPH_NODE_H
#define NETLINE_GRAPH_NODE_H

#include <vector>
#include <string>
#include <set>

namespace Netline::Graph {

class Node {
private:
    std::set<std::size_t> outs;
    std::set<std::size_t> ins;

public:
    std::string identifier = "";
    std::uint32_t potential = 0;
    bool ltd = false;
    int type = 1;

    Node() {}
    Node(std::string _identifier): identifier(_identifier) {}

    /**
    Adds out edge to to
    */
    void add_out_edge(std::size_t to);

    /**
    Adds in edge from from
    */
    void add_in_edge(std::size_t from);

    /**
    Removes out edge to to
    */
    void remove_out_edge(std::size_t to);

    /**
    Removes in edge from from
    */
    void remove_in_edge(std::size_t from);

    /**
    Returns out edges
    */
    const std::set<std::size_t> out_edges() const;

    /**
    Return in edges
    */
    const std::set<std::size_t> in_edges() const;
};

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_NODE_H
