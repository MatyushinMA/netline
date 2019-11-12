#ifndef NETLINE_CONSTANTS_H
#define NETLINE_CONSTANTS_H

#include <cstdint>

namespace Netline {
    struct Constants {
        static const std::uint32_t activation_threshold = 700;
        static const std::uint32_t depression_threshold = 1000;
        static constexpr double linear_skew = 0.3;
        static constexpr double exp_skew = 0.1;
        static constexpr double decay_factor = 0.95;
    };
} // namespace Netline::Graph

#endif // NETLINE_CONSTANTS_H
