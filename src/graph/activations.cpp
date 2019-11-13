#include <netline/graph/activations.h>
#include <netline/constants.h>

namespace Netline::Graph::Activations {

std::uint32_t linear(std::uint32_t potential) {
    if (potential > Constants::activation_threshold) {
        return static_cast<std::uint32_t>(Constants::activation_skew*(potential - Constants::activation_threshold));
    }
    return 0;
}

} // namespace Netline::Graph
