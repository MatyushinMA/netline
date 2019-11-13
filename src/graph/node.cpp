#include <netline/graph/node.h>
#include <netline/constants.h>

#include <algorithm>
#include <cassert>

namespace Netline::Graph {

void Node::norm() {
    double sum_edge_weight = 0.;
    for (const auto edge : outs) {
        sum_edge_weight += edge->weight();
    }
    for (auto edge : outs) {
        edge->norm(sum_edge_weight);
    }
}

void Node::add_out_edge(Edge& edge) {
    auto found = std::find_if(outs.begin(), outs.end(), [&edge](const std::shared_ptr<Edge> arg) { return arg->to() == edge.to(); });
    assert(found == outs.end());
    outs.insert(std::make_shared<Edge>(edge));
}

void Node::add_in_edge(Edge& edge) {
    auto found = std::find_if(ins.begin(), ins.end(), [&edge](const std::shared_ptr<Edge> arg) { return arg->from() == edge.from(); });
    assert(found == ins.end());
    ins.insert(std::make_shared<Edge>(edge));
}

void Node::remove_out_edge(std::size_t to) {
    auto found = std::find_if(outs.begin(), outs.end(), [to](const std::shared_ptr<Edge> arg) { return arg->to() == to; });
    if (found != outs.end()) {
        outs.erase(*found);
    }
}

void Node::remove_in_edge(std::size_t from) {
    auto found = std::find_if(ins.begin(), ins.end(), [from](const std::shared_ptr<Edge> arg) { return arg->from() == from; });
    if (found != ins.end()) {
        ins.erase(*found);
    }
}

void Node::save_stats(std::size_t global_step, Stats::NodeStats&& _stat) {
    stats.emplace(std::make_pair(global_step, std::move(_stat)));
    if (stats.size() > Constants::stats_window) {
        stats.erase(stats.begin());
    }
}

const Stats::NodeStats& Node::get_stats(std::size_t global_step) const {
    assert(stats.count(global_step) == 1);
    return stats.at(global_step);
}

const Stats::NodeStats& Node::get_last_stats() const {
    assert(stats.begin() != stats.end());
    return (stats.end()--)->second;
}

} // namespace Netline::Graph
