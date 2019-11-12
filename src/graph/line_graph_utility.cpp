#include <netline/graph/line_graph.h>
#include <utils/enumerate_util.cpp>

#include <iostream>

namespace Netline::Graph {

void LineGraph::add_node(std::string id) {
    assert(id_map.find(id) == id_map.end());
    nodes.emplace_back(id);
    acquired_potential.push_back(0);
    if (id != "") {
        id_map.insert({{id, nodes.size() - 1}});
    }
}

void LineGraph::add_edge(std::size_t from, std::size_t to) {
    assert((from < nodes.size()) && (to < nodes.size()));
    nodes[from].add_out_edge(to);
    nodes[to].add_in_edge(from);
}

void LineGraph::add_edge(std::string from_id, std::size_t to) {
    assert(id_map.find(from_id) != id_map.end());
    add_edge(id_map[from_id], to);
}

void LineGraph::add_edge(std::size_t from, std::string to_id) {
    assert(id_map.find(to_id) != id_map.end());
    add_edge(from, id_map[to_id]);
}
void LineGraph::add_edge(std::string from_id, std::string to_id) {
    assert((id_map.find(to_id) != id_map.end())
             && (id_map.find(from_id) != id_map.end()));
    add_edge(id_map[from_id], id_map[to_id]);
}

void LineGraph::remove_edge(std::size_t from, std::size_t to) {
    assert((from < nodes.size()) && (to < nodes.size()));
    nodes[from].remove_out_edge(to);
    nodes[to].remove_in_edge(from);
}

void LineGraph::remove_edge(std::string from_id, std::size_t to) {
    assert(id_map.find(from_id) != id_map.end());
    remove_edge(id_map[from_id], to);
}

void LineGraph::remove_edge(std::size_t from, std::string to_id) {
    assert(id_map.find(to_id) != id_map.end());
    remove_edge(from, id_map[to_id]);
}
void LineGraph::remove_edge(std::string from_id, std::string to_id) {
    assert((id_map.find(to_id) != id_map.end())
             && (id_map.find(from_id) != id_map.end()));
    remove_edge(id_map[from_id], id_map[to_id]);
}

void LineGraph::set_input(std::string id) {
    assert(id_map.find(id) != id_map.end());
    inputs.insert(id_map[id]);
}

void LineGraph::set_output(std::string id) {
    assert(id_map.find(id) != id_map.end());
    outputs.insert(id_map[id]);
}

void LineGraph::print() {
    for (const auto [i, node] : enumerate(nodes)) {
        if (node.identifier == "") {
            std::cout << i << "(" << node.potential << ")";
        }
        else {
            std::cout << node.identifier << "(" << node.potential << ")";
        }
        if (node.ltd) {
            std::cout << "*: [ ";
        }
        else {
            std::cout << ": [ ";
        }

        for (const auto j : node.out_edges()) {
            assert(j < nodes.size());
            auto& j_node = nodes[j];
            if (j_node.identifier == "") {
                std::cout << j << " ";
            }
            else {
                std::cout << j_node.identifier << " ";
            }
        }
        std::cout << " ]" << std::endl;
    }
}

} // namespace Netline::Graph