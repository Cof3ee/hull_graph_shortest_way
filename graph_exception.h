#pragma once

#include <stdexcept>

class graph_exception : public std::runtime_error
{
public:
    using runtime_error::runtime_error;
};
