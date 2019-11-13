#include <netline/graph/edge.h>

namespace Netline::Graph {

void Edge::save_stats(std::size_t global_step, Stats::EdgeStats&& _stat) {
    std::cout << "Saving at " << global_step << std::endl;
    stats.emplace(std::make_pair(global_step, std::move(_stat)));
    if (stats.size() > Constants::stats_window) {
        stats.erase(stats.begin());
    }
    std::cout << "Result: " << stats.count(global_step) << std::endl;
}

const Stats::EdgeStats& Edge::get_stats(std::size_t global_step) const {
    std::cout << global_step << " " << stats.count(global_step) << std::endl;
    assert(stats.count(global_step) == 1);
    return stats.at(global_step);
}

const Stats::EdgeStats& Edge::get_last_stats() const {
    assert(stats.begin() != stats.end());
    return (stats.end()--)->second;
}

} // namespace Netline::Graph
