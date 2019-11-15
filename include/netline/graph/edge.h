#ifndef NETLINE_GRAPH_EDGE_H
#define NETLINE_GRAPH_EDGE_H

#include <netline/constants.h>
#include <netline/graph/stats.h>

#include <cstdint>
#include <cassert>
#include <cstddef>
#include <random>
#include <map>
#include <chrono>

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
             std::normal_distribution<double> distribution(1.0, 0.05);
             std::default_random_engine re;
             re.seed(std::chrono::system_clock::now().time_since_epoch().count());
             weight_ = distribution(re);
         }
    Edge(std::size_t _from, std::size_t _to, double _weight):
         from_(_from),
         to_(_to),
         weight_(_weight) {}

    /**
    Getters for node ids
    */
    std::size_t from() const { return from_; }
    std::size_t to() const { return to_; }

    /**
    Getter for weight
    */
    double weight() const { return weight_; }

    /**
    Enforces the edge
    */
    void infix() { weight_ *= Constants::edge_weight_factor; }

    /**
    Norms the weight by given factor
    */
    void norm(double factor) { assert(factor > 0); weight_ /= factor; }

    /**
    Saves stats for given global step
    */
    void save_stats(std::size_t global_step, Stats::EdgeStats&& _stat);

    /**
    Returns stats for given global step
    */
    const Stats::EdgeStats& get_stats(std::size_t global_step) const;

    /**
    Returns last saved stats
    */
    const Stats::EdgeStats& get_last_stats() const;

    /**
    !empty() of stats
    */
    const bool has_stats() const { return !stats.empty(); }
};

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_EDGE_H
