#include <netline/graph/line_graph.h>
#include <netline/graph/activations.h>
#include <netline/graph/conversions.h>
#include <netline/constants.h>
#include <utils/enumerate_util.cpp>

#include <iostream>

namespace Netline::Graph {

void LineGraph::initialize(std::unordered_map<std::string, std::uint32_t> potentials) {
    for (auto [identifier, potential] : potentials) {
        assert(id_map.find(identifier) != id_map.end());
        auto node_num = id_map[identifier];
        nodes[node_num].potential = potential;
    }
}

std::unordered_map<std::string, std::uint32_t> LineGraph::step(std::size_t num_steps, bool* has_activated_nodes) {
    clear_buffers();
    std::unordered_map<std::string, std::uint32_t> ret = std::unordered_map<std::string, std::uint32_t>();
    for (std::size_t num_step = 0; num_step < num_steps; num_step++) {
        for (Node& node : nodes) {
            if (!node.ltd) {
                for (std::size_t j : node.out_edges()) {
                    acquired_potential[j] += Activations::linear(node.potential)*node.type;
                }
                if (node.potential >= Netline::Constants::depression_threshold) {
                    node.ltd = true;
                }
            }
        }
        for (auto&& [node_num, node] : enumerate(nodes)) {
            if (!node.ltd) {
                node.potential = static_cast<std::uint32_t>(Conversions::exponential(node.potential, acquired_potential[node_num])*Netline::Constants::decay_factor);
            }
            else {
                node.potential *= static_cast<std::uint32_t>(node.potential*Constants::decay_factor);
                if (node.potential <= Netline::Constants::activation_threshold) {
                    node.ltd = false;
                }
            }
            if (has_activated_nodes != nullptr) {
                if (node.potential >= Netline::Constants::activation_threshold) {
                    *has_activated_nodes = true;
                }
            }
            if ((num_step = num_steps - 1) && (outputs.find(node_num) != outputs.end())) {
                ret.insert({{node.identifier, node.potential}});
            }
        }
    }
    return ret;
}

std::unordered_map<std::string, std::uint32_t> LineGraph::evaluate() {
    bool flag = false;
    std::unordered_map<std::string, std::uint32_t> ret;
    for (auto&& node : nodes) {
        if (node.potential >= Netline::Constants::activation_threshold) {
            flag = true;
            break;
        }
    }
    while (flag) {
        ret = step(1, &flag);
    }
    return ret;
}

} // namespace Netline::Graph
