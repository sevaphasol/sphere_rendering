#include "geometry/line.hpp"

namespace geometry {

Line::Line( const Vector& direction, const Vector& base_point )
    : direction( direction ), base_point( base_point ) {};

float
Line::getDistance( const Vector& point ) const
{
    return ( ( point - base_point ) && direction ) / direction.getLen();
}

} // namespace geometry
