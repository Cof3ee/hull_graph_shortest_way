#include "shortest_way_finder.h"

using namespace std;

vector<vertex> shortest_way_finder::find(const hull_graph& g, vertex final_vertex)
{
    auto hulls = g.get_hulls();
    vector<vertex> path;
    // Ïóòü âñåãäà íà÷èíàåòñÿ ñ ïåðâîé òî÷êè âíåøíåé âûïóêëîé îáîëî÷êè
    // Íà äàííîì ýòàïå ïðîèçîéäåò îáõîä âñåõ âåðøèí â ãðàôå
    for (const auto& hull : hulls)
    {
        for (auto vertex : hull)
            path.push_back(vertex);
        path.push_back(hull.front());
    }

    auto full_path = path;

    // Äâèæåìñÿ â îáðàòíîì íàïðàâëåíèè è îñòàíàâëèâàåìñÿ íà çàäàííîé òî÷êå
    for (auto it = path.rbegin(); it != path.rend(); ++it)
    {
        auto v = *it;
        full_path.push_back(v);
        if (v == final_vertex)
            break;
    }

    return full_path;
}
