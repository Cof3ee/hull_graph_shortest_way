#include "random_vertex_generator.h"
#include "graph_serializer.h"
#include "hull_graph.h"
#include "shortest_way_finder.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

static double distance(vertex, vertex);

int main(int argc, char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    size_t final_vertex_index = 0;

    bool wait_for_final_vertex_input = argc == 2;

    if (wait_for_final_vertex_input)
    {
        final_vertex_index = stoull(argv[1]);
        cout << "using final vertex index from command line flag: " << final_vertex_index << endl;
    }

    try
    {
        constexpr size_t vertexes_count = 100;
        constexpr uint32_t radius = 100;
        auto vertexes = random_vertex_generator::generate_in_circle(vertexes_count, radius);

        hull_graph g{ vertexes };

        constexpr uint32_t min_vertex_degree = 2;
        constexpr uint32_t max_vertex_degree = 6;
        for (auto v : vertexes)
        {
            auto degree = g.vertex_degree(v);
            assert(degree >= min_vertex_degree && degree <= max_vertex_degree);
        }

        const auto graphml_filename = "graph.graphml";
        ofstream graphml_file(graphml_filename);
        graph_serializer::serialize_to_graphml(graphml_file, g);

        for (size_t i = 0; i < vertexes.size(); ++i)
            cout << i << ": (" << vertexes[i].x << vertexes[i].y << ')' << endl;

        if (!wait_for_final_vertex_input)
        {
            cout << "select index of final vertex" << endl;
            cin >> final_vertex_index;
        }

        auto shortest_way = shortest_way_finder::find(g, vertexes[final_vertex_index]);
        assert(shortest_way.size() > 0);

        const auto shortest_way_csv_filename = "shortest_way.csv";
        ofstream shortest_way_csv{ shortest_way_csv_filename };

        shortest_way_csv << "x,y" << endl;
        for (auto vertex : shortest_way)
            shortest_way_csv << vertex.x << ',' << vertex.y << endl;

        cout << "graph has been serialized into file '" << graphml_filename << '\'' << endl;
        cout << "shortest way path was serialized into file '" << shortest_way_csv_filename << '\'' << endl;

        double shortest_way_cost = 0.;
        for (size_t i = 0; i < shortest_way.size() - 1; ++i)
            shortest_way_cost += distance(shortest_way[i], shortest_way[i + 1]);
        cout << "shortest way total cost: " << shortest_way_cost << endl;
    }
    catch (std::exception& ex)
    {
        cerr << ex.what() << endl;
        exit_code = EXIT_FAILURE;
    }
    catch (...)
    {
        cerr << "caught unhandled exception in the main thread" << endl;
        exit_code = EXIT_FAILURE;
    }

    return exit_code;
}

double distance(vertex v1, vertex v2)
{
    return sqrt(pow(double(v1.x) - v2.x, 2) + pow(double(v1.y) - v2.y, 2));
}