#ifndef NETLINE_GRAPH_ACTIVATIONS_H
#define NETLINE_GRAPH_ACTIVATIONS_H

#include <netline/constants.h>

#include <cstdint>

namespace Netline::Graph::Activations {

/**
ReLU activation
*/
std::uint32_t linear(std::uint32_t potential);

} // namespace Netline::Graph::Activations

#endif // NETLINE_GRAPH_ACTIVATIONS_H
