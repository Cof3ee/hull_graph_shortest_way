#pragma once

#include "hull_graph.h"

class shortest_way_finder
{
public:
	static std::vector<vertex> find( const hull_graph&, vertex final_vertex );
};
