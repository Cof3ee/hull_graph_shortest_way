#pragma once

#include <compare>

struct vertex
{
    double x;
    double y;

    auto operator<=>( const vertex& ) const = default;
};
