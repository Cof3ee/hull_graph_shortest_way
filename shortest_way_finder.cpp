#include "shortest_way_finder.h"

using namespace std;

vector<vertex> shortest_way_finder::find(const hull_graph& g, vertex final_vertex)
{
    auto hulls = g.get_hulls();
    vector<vertex> path;
    // ѕуть всегда начинаетс€ с первой точки внешней выпуклой оболочки
    // Ќа данном этапе произойдет обход всех вершин в графе
    for (const auto& hull : hulls)
    {
        for (auto vertex : hull)
            path.push_back(vertex);
    }

    auto full_path = path;

    // ƒвижемс€ в обратном направлении и останавливаемс€ на заданной точке
    for (auto it = path.rbegin(); it != path.rend(); ++it)
    {
        auto v = *it;
        full_path.push_back(v);
        if (v == final_vertex)
            break;
    }

    return full_path;
}
