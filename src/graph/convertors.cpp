#include <netline/graph/convertors.h>
#include <netline/graph/activations.h>
#include <netline/constants.h>


#include <cstdint>

namespace Netline::Graph::Convertors {

double out_convertor(std::uint32_t out_potential) {
    auto linear_activated = Activations::linear(out_potential);
    auto max_linear_activated = Activations::linear(Constants::max_threshold);
    return static_cast<double>(linear_activated)/static_cast<double>(max_linear_activated);
}

std::uint32_t in_convertor(double in_value) {
    std::uint32_t potential_offset = static_cast<std::uint32_t>(in_value*static_cast<double>(Constants::depression_threshold - Constants::activation_threshold));
    return Constants::activation_threshold + potential_offset - 1;
}

} // namespace Netline::Graph::Convertors
