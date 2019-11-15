#ifndef NETLINE_GRAPH_CONVERTORS_H
#define NETLINE_GRAPH_CONVERTORS_H

#include <cstdint>

namespace Netline::Graph::Convertors {

/**
Output node potential convertor
*/
double out_convertor(std::uint32_t potential);

/**
Input node value convertor
*/
std::uint32_t in_convertor(double in_value);

} // namespace Netline::Graph::Convertors

#endif // NETLINE_GRAPH_CONVERTORS_H
