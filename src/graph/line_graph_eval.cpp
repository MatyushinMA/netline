#include <netline/graph/line_graph.h>
#include <netline/graph/activations.h>
#include <netline/graph/conversions.h>
#include <netline/constants.h>
#include <utils/enumerate_util.cpp>

#include <iostream>
#include <algorithm>

namespace Netline::Graph {

void LineGraph::feed(std::unordered_map<std::string, std::uint32_t> potentials) {
    for (auto [identifier, potential] : potentials) {
        assert(id_map.find(identifier) != id_map.end());
        auto node_num = id_map[identifier];
        nodes[node_num].potential = potential;
    }
}

std::unordered_map<std::string, std::uint32_t> LineGraph::step(std::size_t num_steps, std::size_t global_step, bool* has_activated_nodes) {
    if (has_activated_nodes != nullptr) {
        *has_activated_nodes = false;
    }
    clear_buffers();
    std::unordered_map<std::string, std::uint32_t> ret = std::unordered_map<std::string, std::uint32_t>();
    for (std::size_t num_step = 0; num_step < num_steps; num_step++) {
        for (Node& node : nodes) {
            if (!node.ltd) {
                double sum_edge_weight = 0.;
                for (std::shared_ptr<Edge> edge : node.out_edges()) {
                    auto conveyed_potential = static_cast<std::uint32_t>(Activations::linear(node.potential)*edge->weight());
                    if (conveyed_potential >= Constants::edge_activation_threshold) {
                        acquired_potential[edge->to()] += static_cast<int64_t>(conveyed_potential)*static_cast<int>(node.type);
                        edge->infix();
                    }
                    sum_edge_weight += edge->weight();
                }
                for (std::shared_ptr<Edge> edge : node.out_edges()) {
                    edge->norm(sum_edge_weight);
                }
                if (node.potential >= Constants::depression_threshold) {
                    node.ltd = true;
                }
            }
        }
        for (auto&& [node_num, node] : enumerate(nodes)) {
            if (!node.ltd) {
                auto new_potential = static_cast<std::int64_t>(Conversions::exponential(node.potential, acquired_potential[node_num])*Constants::decay_factor);
                if (new_potential > static_cast<std::int64_t>(Constants::max_threshold)) {
                    node.potential = Constants::max_threshold;
                }
                else if (new_potential <= 0) {
                    node.potential = 0;
                }
                else {
                    node.potential = static_cast<std::uint32_t>(new_potential);
                }
            }
            else {
                node.potential = static_cast<std::uint32_t>(node.potential*Constants::decay_factor);
                if (node.potential <= Constants::activation_threshold) {
                    node.ltd = false;
                }
            }
            if (has_activated_nodes != nullptr) {
                if (node.potential >= Constants::activation_threshold) {
                    *has_activated_nodes = true;
                }
            }
            if ((num_step == num_steps - 1) && (outputs.find(node_num) != outputs.end())) {
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
        if (node.potential >= Constants::activation_threshold) {
            flag = true;
            break;
        }
    }
    std::size_t global_step = 0;
    while (flag) {
        ret = step(1, global_step++, &flag);
    }
    return ret;
}

} // namespace Netline::Graph
