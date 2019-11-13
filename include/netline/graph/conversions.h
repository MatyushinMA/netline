#ifndef NETLINE_GRAPH_CONVERSIONS_H
#define NETLINE_GRAPH_CONVERSIONS_H

#include <cstdint>

namespace Netline::Graph::Conversions {

std::int64_t linear(std::uint32_t potential, std::int64_t acquired_potential);
std::int64_t exponential(std::uint32_t potential, std::int64_t acquired_potential);

} // namespace Netline::Graph

#endif // NETLINE_GRAPH_CONVERSIONS_H
