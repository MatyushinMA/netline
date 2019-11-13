#include <netline/graph/stats.h>

#include <iostream>

namespace Netline::Graph::Stats {

std::ostream& operator<<(std::ostream& stream, const NodeStats& stats) {
    stream << "|activated: " << stats.activated << std::endl;
    stream << "|depressed: " << stats.depressed << std::endl;
    stream << "|potential: " << stats.potential << std::endl;
    stream << "|num_activated_ins: " << stats.num_activated_ins << std::endl;
    stream << "|num_activated_outs: " << stats.num_activated_outs << std::endl;
    stream << "|max_outs_weight: " << stats.max_outs_weight << std::endl;
    stream << "|median_outs_weight: " << stats.median_outs_weight;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const EdgeStats& stats) {
    stream << "|activated: " << stats.activated << std::endl;
    stream << "|weight: " << stats.weight << std::endl;
    stream << "|conveyed_potential: " << stats.conveyed_potential;
    return stream;
}

} // namespace Netline::Graph::Stats
