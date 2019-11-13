#include <netline/graph/line_graph.h>
#include <netline/graph/activations.h>
#include <netline/graph/conversions.h>
#include <netline/constants.h>
#include <netline/graph/stats.h>
#include <utils/enumerate_util.cpp>
#include <utils/median_util.cpp>

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
            Stats::NodeStats node_stat;
            node_stat.potential = node.potential;
            if (global_step > 0) {
                for (std::shared_ptr<Edge> edge : node.in_edges()) {
                    auto prev_step_edge_stat = edge->get_stats(global_step - 1);
                    if (prev_step_edge_stat.activated) {
                        node_stat.num_activated_ins++;
                    }
                }
            }
            if (!node.ltd) {
                double sum_edge_weight = 0.;
                std::vector<double> edge_weights;
                for (std::shared_ptr<Edge> edge : node.out_edges()) {
                    Stats::EdgeStats edge_stat;
                    edge_weights.push_back(edge->weight());
                    edge_stat.weight = edge->weight();
                    node_stat.max_outs_weight = std::max(node_stat.max_outs_weight, edge->weight());
                    auto activated_potential = Activations::linear(node.potential);
                    node_stat.activated = (activated_potential > 0);
                    auto conveyed_potential = static_cast<std::uint32_t>(activated_potential*edge->weight());
                    if (conveyed_potential >= Constants::edge_activation_threshold) {
                        acquired_potential[edge->to()] += static_cast<int64_t>(conveyed_potential)*static_cast<int>(node.type);
                        edge->infix();
                        node_stat.num_activated_outs++;
                        edge_stat.activated = true;
                        edge_stat.conveyed_potential = conveyed_potential;
                    }
                    sum_edge_weight += edge->weight();
                    edge->save_stats(global_step, std::move(edge_stat));
                }
                node_stat.median_outs_weight = median(edge_weights);
                for (std::shared_ptr<Edge> edge : node.out_edges()) {
                    edge->norm(sum_edge_weight);
                }
                node.ltd = (node.potential >= Constants::depression_threshold);
            }
            node_stat.depressed = node.ltd;
            node.save_stats(global_step, std::move(node_stat));
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
                node.ltd = (node.potential > Constants::activation_threshold);
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
        std::cout << *this << std::endl;
    }
    return ret;
}

} // namespace Netline::Graph
