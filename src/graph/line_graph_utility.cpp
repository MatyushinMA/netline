#include <netline/graph/line_graph.h>
#include <utils/enumerate_util.cpp>

#include <iostream>

namespace Netline::Graph {

void LineGraph::add_node(std::string id, NodeType type) {
    assert(id_map.find(id) == id_map.end());
    nodes.emplace_back(id, type);
    acquired_potential.push_back(0);
    if (id != "") {
        id_map.insert({{id, nodes.size() - 1}});
    }
}

void LineGraph::add_edge(std::size_t from, std::size_t to) {
    assert((from < nodes.size()) && (to < nodes.size()));
    Edge new_edge = Edge(from, to);
    nodes[from].add_out_edge(new_edge);
    nodes[to].add_in_edge(new_edge);
    nodes[from].norm();
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

std::ostream& operator<<(std::ostream &stream, const LineGraph& g) {
    for (const auto [i, node] : enumerate(g.nodes)) {
        if (node.type == Excitatory) {
            stream << "+";
        }
        else {
            stream << "-";
        }
        if (node.identifier == "") {
            stream << i << "(" << node.potential << ")";
        }
        else {
            stream << node.identifier << "(" << node.potential << ")";
        }
        if (node.ltd) {
            stream << "X: [ ";
        }
        else {
            stream << ": [ ";
        }

        for (const std::shared_ptr<Edge> edge : node.out_edges()) {
            assert(edge->to() < g.nodes.size());
            auto& to_node = g.nodes[edge->to()];
            if (to_node.identifier == "") {
                stream << edge->to();
            }
            else {
                stream << to_node.identifier;
            }
            stream << "(" << edge->weight() << ") ";
        }
        stream << "]" << std::endl;
        stream << node.get_last_stats() << std::endl;
    }
    return stream;
}

} // namespace Netline::Graph
