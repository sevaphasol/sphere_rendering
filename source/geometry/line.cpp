#include "geometry/line.hpp"

namespace geometry {

Line::Line( const Vector& direction, const Vector& base_point )
    : direction( direction ), base_point( base_point ) {};

float
Line::GetDistance( const Vector& point ) const
{
    return ( CalcVecMulModule( ( point - base_point ), direction ) ) / direction.GetLen();
}

} // namespace geometry
