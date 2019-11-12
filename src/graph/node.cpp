#include <netline/graph/node.h>

namespace Netline::Graph {

void Node::add_out_edge(std::size_t to) {
    outs.insert(to);
}

void Node::add_in_edge(std::size_t from) {
    ins.insert(from);
}

void Node::remove_out_edge(std::size_t to) {
    outs.erase(to);
}

void Node::remove_in_edge(std::size_t from) {
    ins.erase(from);
}

const std::set<std::size_t> Node::out_edges() const {
    return outs;
}

const std::set<std::size_t> Node::in_edges() const {
    return ins;
}

} // namespace Netline::Graph
