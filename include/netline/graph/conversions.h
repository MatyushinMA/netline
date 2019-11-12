#ifndef NETLINE_GRAPH_CONVERSIONS_H
#define NETLINE_GRAPH_CONVERSIONS_H

#include <cstdint>

namespace Netline::Graph::Conversions {

std::uint32_t exponential(std::uint32_t potential, std::uint32_t acquired_potential);

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_CONVERSIONS_H
