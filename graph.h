#pragma once

#include "vertex.h"

#include "graph_exception.h"

#include <vector>
#include <map>
#include <optional>

class graph
{
public:
    void add_vertex( vertex );
    void remove_vertex( vertex );

    void add_edge( vertex src, vertex dst, double weight );
    void remove_edge( vertex src, vertex dst );

    bool contains( vertex );

    std::vector<vertex> get_connected_vertexes( vertex ) const;

    int vertex_degree( vertex );

    bool is_connected() const;

    bool vertexes_connected( vertex v1, vertex v2 );

    const std::vector<std::vector<std::optional<double>>>& get_adjacency_matrix() const;
    const std::map<vertex, size_t>& get_vertex_to_index() const;

private:
    vertex get_vertex_by_index( size_t index ) const;

private:
    // nullopt weight means that there is no edge between vertexes
    std::vector<std::vector<std::optional<double>>> adjacency_matrix_;
    std::map<vertex, size_t> vertex_to_index_;
};
