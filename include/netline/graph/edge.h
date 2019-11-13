#ifndef NETLINE_GRAPH_EDGE_H
#define NETLINE_GRAPH_EDGE_H

#include <netline/constants.h>
#include <netline/graph/stats.h>

#include <cstdint>
#include <cassert>
#include <cstddef>
#include <random>
#include <map>

namespace Netline::Graph {

class Edge {
private:
    std::size_t from_;
    std::size_t to_;
    double weight_;
    std::map<std::size_t, Stats::EdgeStats> stats;

public:
    Edge(std::size_t _from, std::size_t _to):
         from_(_from),
         to_(_to) {
             std::uniform_real_distribution<double> distribution(0, 1);
             std::default_random_engine re;
             weight_ = distribution(re);
         }
    Edge(std::size_t _from, std::size_t _to, double _weight):
         from_(_from),
         to_(_to),
         weight_(_weight) {}

    std::size_t from() const { return from_; }
    std::size_t to() const { return to_; }
    double weight() const { return weight_; }
    void infix() { weight_ *= Constants::edge_weight_factor; }
    void norm(double factor) { assert(factor > 0); weight_ /= factor; }
    void save_stats(std::size_t global_step, Stats::EdgeStats&& _stat);
    const Stats::EdgeStats& get_stats(std::size_t global_step) const;
    const Stats::EdgeStats& get_last_stats() const;
};

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_EDGE_H
