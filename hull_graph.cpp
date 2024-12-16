#include "hull_graph.h"
#include "hull_graph.h"
#include "hull_graph.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>

using namespace std;

hull_graph::hull_graph( vector<vertex> vertexes )
{
    vector<vector<vertex>> hulls = find_all_convex_hulls(vertexes);

    for (const auto& hull : hulls)
    {
        // ���������� ���� ����� �������� � ����
        for (size_t i = 0; i < hull.size(); ++i)
        {
            auto src = hull[i];
            add_vertex(src);
        }

        // ���������� �������� ����� �����, ����� ������ � ���������
        for (size_t i = 0; i < hull.size() - 1; ++i)
            add_edge_with_distance_weight(hull[i], hull[i + 1]);

        // ��������� ������ � ��������� ����� ��������
        add_edge_with_distance_weight(hull.front(), hull.back());
    }

    assert(hulls.size() > 0);

    // �������� ���� ����� ����� ������ �������� ���������
    for (size_t i = 0; i < hulls.size() - 1; ++i)
        add_edge_with_distance_weight(hulls[i][0], hulls[i + 1][0]);

    assert(vertexes.size() <= 2);

    // ��� ���������� �������� �������� ���������� ��� ������� ��� �����
    // �� ����� ����� �������� �������� ��� ��������� �����, �� ���������� ����������
    if (vertexes.size() > 0)
    {
        // �������� ���������� ����� ������ ��������� ������ � ����� ������� �� ����� ���������� �������� ��������
        auto src_v = vertexes[0];
        auto hull_v1 = hulls.back()[0];
        auto hull_v2 = hulls.back().back();

        add_vertex(src_v);
        add_edge_with_distance_weight(src_v, hull_v1);
        add_edge_with_distance_weight(src_v, hull_v2);

        if (vertexes.size() == 2)
        {
            auto dst = vertexes[1];
            add_vertex(dst);

            add_edge_with_distance_weight(src_v, dst);
            add_edge_with_distance_weight(dst, hull_v2);
        }
    }

    assert(is_connected());

    hulls_ = hulls;
}

const vector<vector<vertex>>& hull_graph::get_hulls() const
{
    return hulls_;
}

void hull_graph::add_edge_with_distance_weight(vertex v1, vertex v2)
{
    auto dist = distance(v1, v2);
    add_edge(v1, v2, dist);
}

// ������� ��� ���������� ���� ���������� �������� ��������
vector<vector<vertex>> hull_graph::find_all_convex_hulls(vector<vertex>& points)
{
    vector<vector<vertex>> allHulls;
    while (points.size() >= 3)
    {
        vector<vertex> hull = graham_scan(points);
        allHulls.push_back(hull);

        // ������� �����, ������� ������ � ������� ��������
        vector<vertex> remaining_vertexs;
        for (const auto p : points)
        {
            if (find(hull.begin(), hull.end(), p) == hull.end())
                remaining_vertexs.push_back(p);
        }
        points = remaining_vertexs;
    }
    return allHulls;
}

vector<vertex> hull_graph::graham_scan(vector<vertex>& points)
{
    sort(points.begin(), points.end(), [](const vertex& a, const vertex& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
        });

    vector<vertex> lower;
    for (auto p : points)
    {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower[lower.size() - 1], p) <= 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    vector<vertex> upper;
    for (auto it = points.rbegin(); it != points.rend(); ++it)
    {
        const auto& p = *it;
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper[upper.size() - 1], p) <= 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

double hull_graph::distance(vertex v1, vertex v2)
{
    return sqrt(pow(double(v1.x) - v2.x, 2) + pow(double(v1.y) - v2.y, 2));
}

double hull_graph::cross(const vertex& o, const vertex& a, const vertex& b) 
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
