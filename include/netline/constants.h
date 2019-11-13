#ifndef NETLINE_CONSTANTS_H
#define NETLINE_CONSTANTS_H

#include <cstdint>

namespace Netline {

    struct Constants {
        static const std::uint32_t activation_threshold = 700;
        static const std::uint32_t edge_activation_threshold = 200;
        static const std::uint32_t depression_threshold = 1000;
        static const std::uint32_t max_threshold = 2000;
        static constexpr double activation_skew = 2.83;
        static constexpr double exponential_skew = 0.001;
        static constexpr double decay_factor = 0.95;
        static constexpr double edge_weight_factor = 1.1;
    };

} // namespace Netline::Graph

#endif // NETLINE_CONSTANTS_H
