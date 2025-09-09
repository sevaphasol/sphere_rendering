#include "geometry/sphere.hpp"

namespace geometry {

Sphere::Sphere( const Vector& center, float radius ) : center( center ), radius( radius ) {}

bool
Sphere::lineDoesIntersect( const Line& line ) const
{
    return line.getDistance( center ) <= radius;
}

// Call only if raIntersect == true
Vector
Sphere::getIntersectionWithRay( const Line& line ) const
{
    if ( !lineDoesIntersect( line ) )
    {
        return { NAN, NAN, NAN };
    }

    Vector cam = line.base_point;
    Vector sph = center;
    Vector a   = line.direction;
    Vector b   = cam - sph;

    float a_len = a.getLen();
    float b_len = b.getLen();

    float cos_phi    = ( a * b ) / ( a_len * b_len );
    float cos_phi_sq = cos_phi * cos_phi;

    float b_len_sq  = b_len * b_len;
    float b_cos_phi = b_len * cos_phi;

    float r_sq = radius * radius;

    float t = -( b_cos_phi - sqrt( ( b_len_sq * ( cos_phi_sq - 1 ) ) + r_sq ) ) / a_len;

    return cam + a * t;
}

} // namespace geometry
