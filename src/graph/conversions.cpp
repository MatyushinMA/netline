#include <netline/graph/conversions.h>
#include <netline/constants.h>

#include <math.h>
#include <iostream>

namespace Netline::Graph::Conversions {

std::int64_t linear(std::uint32_t potential, std::int64_t acquired_potential) {
    return static_cast<std::int64_t>(static_cast<std::int64_t>(potential) + acquired_potential);
}

std::int64_t exponential(std::uint32_t potential, std::int64_t acquired_potential) {
    return static_cast<std::int64_t>(Constants::exponential_skew*static_cast<std::int64_t>(potential)*acquired_potential + static_cast<std::int64_t>(potential) + acquired_potential);
}

} // namespace Netline::Graph::Conversions
