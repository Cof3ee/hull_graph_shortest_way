#pragma once

#include "graph.h"

class graph_serializer
{
public:
    // Сериализация графа в формат graphml
    // Результирующий файл содержит список вершин с координатами x,y, а также
    // список ребер с весами - расстояниями между точками
    static void serialize_to_graphml( std::ostream& output, const graph& );

private:
    static double distance(vertex, vertex);
};
