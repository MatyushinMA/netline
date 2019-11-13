#ifndef NETLINE_GRAPH_STATS_H
#define NETLINE_GRAPH_STATS_H

#include <cstdint>
#include <iostream>

namespace Netline::Graph::Stats {

struct NodeStats {
    bool activated = false;
    bool depressed = false;
    std::uint32_t potential = 0;
    std::size_t num_activated_ins = 0;
    std::size_t num_activated_outs = 0;
    double max_outs_weight = 0;
    double median_outs_weight = 0;
};

std::ostream& operator<<(std::ostream& stream, const NodeStats& stats);

struct EdgeStats {
    bool activated = false;
    double weight = 0;
    std::uint32_t conveyed_potential = 0;
};

std::ostream& operator<<(std::ostream& stream, const EdgeStats& stats);

} // namespace Netline::Graph::Stats

#endif // NETLINE_GRAPH_STATS_H
