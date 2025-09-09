#include "geometry/sphere.hpp"

namespace geometry {

Sphere::Sphere( const Vector& center, float radius, const sf::Color& color )
    : center( center ), radius( radius ), color( color ) {};

bool
Sphere::LineDoesIntersect( const Line& line ) const
{
    return line.GetDistance( center ) <= radius;
}

Vector
Sphere::GetIntersectionWithLine( const Line& line ) const
{
    if ( !LineDoesIntersect( line ) )
    {
        return { NAN, NAN, NAN };
    }

    Vector cam = line.base_point;
    Vector sph = center;
    Vector a   = line.direction;
    Vector b   = cam - sph;

    float a_len = a.GetLen();
    float b_len = b.GetLen();

    float cos_phi    = ( a, b ) / ( a_len * b_len );
    float cos_phi_sq = cos_phi * cos_phi;

    float b_len_sq  = b_len * b_len;
    float b_cos_phi = b_len * cos_phi;

    float r_sq = radius * radius;

    float t = -( b_cos_phi - sqrt( ( b_len_sq * ( cos_phi_sq - 1 ) ) + r_sq ) ) / a_len;

    return cam + a * t;
}

} // namespace geometry
