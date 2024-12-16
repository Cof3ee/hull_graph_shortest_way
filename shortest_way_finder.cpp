#include "shortest_way_finder.h"

using namespace std;

vector<vertex> shortest_way_finder::find(const hull_graph& g, vertex final_vertex)
{
    auto hulls = g.get_hulls();
    vector<vertex> path;
    // ���� ������ ���������� � ������ ����� ������� �������� ��������
    // �� ������ ����� ���������� ����� ���� ������ � �����
    for (const auto& hull : hulls)
    {
        for (auto vertex : hull)
            path.push_back(vertex);
    }

    auto full_path = path;

    // �������� � �������� ����������� � ��������������� �� �������� �����
    for (auto it = path.rbegin(); it != path.rend(); ++it)
    {
        auto v = *it;
        full_path.push_back(v);
        if (v == final_vertex)
            break;
    }

    return full_path;
}
