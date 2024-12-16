#include "random_vertex_generator.h"

#include <cmath>
#include <random>
#include <numbers>
#include <set>

using namespace std;

vector<vertex> random_vertex_generator::generate_in_circle( size_t count, uint32_t radius )
{
    random_device rd;
    mt19937 generator{ rd() };
    uniform_real_distribution<double> radius_distribution( 0., radius );
    uniform_real_distribution<double> angle_distribution(0., 2. * numbers::pi);

    set<vertex> result;
    while( result.size() < count )
    {
        const double random_radius = radius_distribution( generator );
        const double angle = angle_distribution( generator );

        result.insert( { random_radius * cos(angle), random_radius * sin(angle)});
    }

    return { result.begin(), result.end() };
}
