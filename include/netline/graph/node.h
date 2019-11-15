#ifndef NETLINE_GRAPH_NODE_H
#define NETLINE_GRAPH_NODE_H

#include <netline/graph/edge.h>
#include <netline/graph/stats.h>

#include <string>
#include <set>
#include <map>

namespace Netline::Graph {

enum NodeType {
    Excitatory = 1,
    Inhibitory = -1
};

class Node {
private:
    std::set<std::shared_ptr<Edge>> outs;
    std::set<std::shared_ptr<Edge>> ins;
    std::map<std::size_t, Stats::NodeStats> stats;

public:
    std::string identifier = "";
    std::uint32_t potential = 0;
    bool ltd = false;
    NodeType type = Excitatory;

    Node() {}
    Node(std::string _identifier, NodeType _type):
         identifier(_identifier),
         type(_type) {}

    /**
    Norms out edges so their weights sums to 1
    */
    void norm();

    /**
    Adds out edge
    */
    void add_out_edge(std::shared_ptr<Edge> edge);

    /**
    Adds in edge
    */
    void add_in_edge(std::shared_ptr<Edge> edge);

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
    const std::set<std::shared_ptr<Edge>>& out_edges() const { return outs; }

    /**
    Return in edges
    */
    const std::set<std::shared_ptr<Edge>>& in_edges() const { return ins; }

    /**
    Saves stats for given global step
    */
    void save_stats(std::size_t global_step, Stats::NodeStats&& _stat);

    /**
    Returns stats for given global step
    */
    const Stats::NodeStats& get_stats(std::size_t global_step) const;

    /**
    Returns last recorded stats
    */
    const Stats::NodeStats& get_last_stats() const;

    /**
    !empty() of stats
    */
    const bool has_stats() const { return !stats.empty(); }
};

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_NODE_H
