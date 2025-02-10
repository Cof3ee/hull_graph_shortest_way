#pragma once

#include "vertex.h"

#include <cstddef>
#include <vector>
#include <cstdint>

class random_vertex_generator
{
public:
    static std::vector<vertex> generate_in_circle( size_t count, uint32_t radius );
};
