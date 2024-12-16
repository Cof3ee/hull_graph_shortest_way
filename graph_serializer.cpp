#include "graph_serializer.h"
#include "graph_serializer.h"

#include <cassert>
#include <string>
#include <ostream>

using namespace std;

void graph_serializer::serialize_to_graphml( ostream& output, const graph& g )
{
    output << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\">" << endl;
    output << "  <key id=\"x\" for=\"node\" attr.name=\"x\" attr.type=\"double\"/>" << endl;
    output << "  <key id=\"y\" for=\"node\" attr.name=\"y\" attr.type=\"double\"/>" << endl;
    output << "  <key id=\"weight\" for=\"edge\" attr.name=\"weight\" attr.type=\"double\"/>" << endl;

    output << "  <graph id=\"G\" edgedefault=\"undirected\">" << endl;

    const auto& vertex_to_index = g.get_vertex_to_index();
    for( auto [ vertex, index ] : vertex_to_index )
    {
        const auto node_id = "n" + to_string( index );
        output << "    <node id=\"" << node_id << "\">" << endl;
        output << "      <data key=\"x\">" << vertex.x << "</data>" << endl;
        output << "      <data key=\"y\">" << vertex.y << "</data>" << endl;
        output << "    </node>" << endl;
    }

    const auto& adjacency_matrix = g.get_adjacency_matrix();

    for( auto [ vertex, index ] : vertex_to_index )
    {
        const auto source_id = "n" + to_string( index );
        auto connected_vertexes = g.get_connected_vertexes( vertex );
        for( auto connected_vertex : connected_vertexes )
        {
            const auto connected_vertex_index = vertex_to_index.at(connected_vertex);
            const auto weight = adjacency_matrix[index][connected_vertex_index];
            assert(weight.has_value());

            const auto target_id = "n" + to_string( vertex_to_index.at( connected_vertex ) );
            output << "    <edge source=\"" << source_id << "\" target=\"" << target_id << "\">" << endl;
            output << "      <data key=\"weight\">" << *weight << "</data>" << endl;
            output << "    </edge>" << endl;
        }
    }

    output << "  </graph>" << endl;
    output << "</graphml>";
}

double graph_serializer::distance(vertex v1, vertex v2)
{
    return sqrt(pow(double(v1.x) - v2.x, 2) + pow(double(v1.y) - v2.y, 2));
}
