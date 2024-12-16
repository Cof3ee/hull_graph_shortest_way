#pragma once

#include "vertex.h"
#include "graph.h"

class hull_graph : public graph
{
public:
	// ������ ����, � ������� ��������� ����� � ������ ������ �������� ��������, � ����� ���������� ���������
	// �������� �������� ����� �� ������ ���������� ����� �����.
	hull_graph( std::vector<vertex> );

	const std::vector<std::vector<vertex>>& get_hulls() const;

private:
	void add_edge_with_distance_weight(vertex, vertex);

	static std::vector<std::vector<vertex>> find_all_convex_hulls(std::vector<vertex>& vertexes);

	static std::vector<vertex> graham_scan(std::vector<vertex>& points);

	static double distance( vertex, vertex );

	static double cross(const vertex& o, const vertex& a, const vertex& b);

private:
	std::vector<std::vector<vertex>> hulls_;
};
