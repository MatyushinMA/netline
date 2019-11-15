#ifndef NETLINE_CONSTANTS_H
#define NETLINE_CONSTANTS_H

#include <cstdint>
#include <iostream>

namespace Netline {

    struct Constants {
        /**
        Starting from this potential value neurons activate
        */
        static const std::uint32_t activation_threshold = 700;

        /**
        Starting from this potential value edges activate
        */
        static const std::uint32_t edge_activation_threshold = 0;

        /**
        Starting from this potential value neurons get LTD
        */
        static const std::uint32_t depression_threshold = 1500;

        /**
        Max value for potential
        */
        static const std::uint32_t max_threshold = 2000;

        /**
        Skew of ReLU activation
        */
        static constexpr double activation_skew = 2.83;

        /**
        Skew of exponential activation
        */
        static constexpr double exponential_skew = 0.001;

        /**
        Potential step-wise decay factor
        */
        static constexpr double decay_factor = 0.95;

        /**
        Edge weight activation-wise multiplexer
        */
        static constexpr double edge_weight_factor = 1.1;

        /**
        Num of last steps with recorded stats
        */
        static const std::size_t stats_window = 100;
    };

} // namespace Netline::Graph

#endif // NETLINE_CONSTANTS_H
