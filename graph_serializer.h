#pragma once

#include "graph.h"

class graph_serializer
{
public:
    // ������������ ����� � ������ graphml
    // �������������� ���� �������� ������ ������ � ������������ x,y, � �����
    // ������ ����� � ������ - ������������ ����� �������
    static void serialize_to_graphml( std::ostream& output, const graph& );

private:
    static double distance(vertex, vertex);
};
