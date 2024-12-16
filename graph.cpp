#include "graph.h"

#include <queue>

using namespace std;

void graph::add_vertex( vertex v )
{
    if( vertex_to_index_.contains( v ) )
        throw graph_exception( "graph already contains vertex" );

    vertex_to_index_[v] = adjacency_matrix_.size();

    auto new_row = adjacency_matrix_.emplace_back( adjacency_matrix_.size() );

    for( auto& row : adjacency_matrix_ )
        row.push_back( nullopt );
}

void graph::remove_vertex( vertex v )
{
    if( !vertex_to_index_.contains( v ) )
        throw graph_exception( "graph already contains vertex" );

    auto index = vertex_to_index_[v];
    for( size_t i = 0; i < adjacency_matrix_.size(); ++i )
    {
        adjacency_matrix_[i].erase( adjacency_matrix_[i].begin() + index );
    }
    adjacency_matrix_.erase( adjacency_matrix_.begin() + index );

    vertex_to_index_.erase( v );
}

void graph::add_edge( vertex src, vertex dst, double weight )
{
    auto src_it = vertex_to_index_.find( src );
    if( src_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    auto dst_it = vertex_to_index_.find( dst );
    if( dst_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    adjacency_matrix_[src_it->second][dst_it->second] = weight;
    adjacency_matrix_[dst_it->second][src_it->second] = weight;
}

void graph::remove_edge( vertex src, vertex dst )
{
    auto src_it = vertex_to_index_.find( src );
    if( src_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    auto dst_it = vertex_to_index_.find( dst );
    if( dst_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    adjacency_matrix_[src_it->second][dst_it->second] = nullopt;
    adjacency_matrix_[dst_it->second][src_it->second] = nullopt;
}

bool graph::contains( vertex v )
{
    return vertex_to_index_.contains( v );
}

vector<vertex> graph::get_connected_vertexes( vertex ref ) const
{
    auto ref_it = vertex_to_index_.find( ref );
    if( ref_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    const auto& ref_row = adjacency_matrix_[ref_it->second];
    vector<vertex> result;
    for( size_t i = 0; i < ref_row.size(); ++i )
    {
        if( ref_row[i] == nullopt )
            continue;

        for( const auto& [ vertex, vertex_index ] : vertex_to_index_ )
        {
            if( vertex_index == i )
            {
                result.push_back( vertex );
                break;
            }
        }
    }

    return result;
}

int graph::vertex_degree( vertex v )
{
    auto vertex_index = vertex_to_index_[v];
    const auto& vertex_row = adjacency_matrix_[vertex_index];

    int degree = 0;
    for( auto weight : vertex_row )
    {
        if( weight != nullopt )
            ++degree;
    }

    return degree;
}

bool graph::is_connected() const
{
    map<vertex, bool> visited;
     for( auto [vertex, _] : vertex_to_index_ )
         visited[vertex] = false;

     queue<vertex> s;
     s.push( vertex_to_index_.begin()->first );

     while( !s.empty() )
     {
         auto v = s.front();
         s.pop();

         auto v_index = vertex_to_index_.at( v );
         for( size_t adjacent_v_index = 0; adjacent_v_index < adjacency_matrix_[v_index].size(); adjacent_v_index++ )
         {
             if( adjacency_matrix_[v_index][adjacent_v_index] == nullopt )
                 continue;

             auto vertex = get_vertex_by_index( adjacent_v_index );
             if( !visited[vertex] )
             {
                 visited[vertex] = true;
                 s.push( vertex );
             }
         }
     }

    bool all_visited = visited.size() == vertex_to_index_.size();
    if( !all_visited )
        return false;

    for( auto [_, vertex_visited] : visited )
        all_visited &= vertex_visited;

    return all_visited;
}

bool graph::vertexes_connected( vertex v1, vertex v2 )
{
    auto src_it = vertex_to_index_.find( v1 );
    if( src_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    auto dst_it = vertex_to_index_.find( v2 );
    if( dst_it == vertex_to_index_.end() )
        throw graph_exception( "graph doesnt contain vertex" );

    return adjacency_matrix_[src_it->second][dst_it->second] != nullopt;
}

const vector<vector<optional<double>>>& graph::get_adjacency_matrix() const
{
    return adjacency_matrix_;
}

const map<vertex, size_t>& graph::get_vertex_to_index() const
{
    return vertex_to_index_;
}

vertex graph::get_vertex_by_index( size_t index ) const
{
    for( auto [ v, v_index ] : vertex_to_index_ )
    {
        if( v_index == index )
            return v;
    }

    throw graph_exception( "vertex with specified index was not found" );
}
