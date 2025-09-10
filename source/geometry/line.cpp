#include "geometry/line.hpp"

namespace geometry {

Line::Line( const Vector& dir, const Vector& base_point )
    : dir_( dir ), base_point_( base_point ) {};

float
Line::GetDistance( const Vector& point ) const
{
    return ( CalcVecMulModule( ( point - base_point_ ), dir_ ) ) / dir_.GetLen();
}

Vector
Line::GetDirectionVector() const
{
    return dir_;
}

Vector
Line::GetBasePoint() const
{
    return base_point_;
}

} // namespace geometry
