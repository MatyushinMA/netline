#include <netline/graph/conversions.h>
#include <netline/constants.h>

#include <math.h>
#include <iostream>

namespace Netline::Graph::Conversions {

std::uint32_t exponential(std::uint32_t potential, std::uint32_t acquired_potential) {
    return static_cast<std::uint32_t>(exp(log(1 + potential) + Constants::exp_skew*acquired_potential) - 1);
}

} // namespace Netline::Graph::Conversions
