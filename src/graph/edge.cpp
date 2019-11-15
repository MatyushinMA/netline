#include <netline/graph/edge.h>

namespace Netline::Graph {

void Edge::save_stats(std::size_t global_step, Stats::EdgeStats&& _stat) {
    stats[global_step] = std::move(_stat);
    if (stats.size() > Constants::stats_window) {
        stats.erase(stats.begin());
    }
}

const Stats::EdgeStats& Edge::get_stats(std::size_t global_step) const {
    assert(stats.count(global_step) == 1);
    return stats.at(global_step);
}

const Stats::EdgeStats& Edge::get_last_stats() const {
    assert(stats.begin() != stats.end());
    return stats.rbegin()->second;
}

} // namespace Netline::Graph
