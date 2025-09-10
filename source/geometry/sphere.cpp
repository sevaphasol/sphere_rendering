#include "geometry/sphere.hpp"

namespace geometry {

Sphere::Sphere( const Vector& center, float radius, const sf::Color& color )
    : center_( center ), radius_( radius ), color_( color ) {};

bool
Sphere::LineDoesIntersect( const Line& line ) const
{
    return line.GetDistance( center_ ) <= radius_;
}

Vector
Sphere::GetIntersectionWithLine( const Line& line ) const
{
    if ( !LineDoesIntersect( line ) )
    {
        return Vector( std::numeric_limits<float>::quiet_NaN(),
                       std::numeric_limits<float>::quiet_NaN(),
                       std::numeric_limits<float>::quiet_NaN() );
    }

    Vector r0  = line.GetBasePoint();
    Vector sph = center_;
    Vector a   = line.GetDirectionVector();
    Vector b   = r0 - sph;

    float a_len = a.GetLen();
    float b_len = b.GetLen();

    float cos_phi    = ( a, b ) / ( a_len * b_len );
    float cos_phi_sq = cos_phi * cos_phi;

    float b_len_sq  = b_len * b_len;
    float b_cos_phi = b_len * cos_phi;

    float r_sq = radius_ * radius_;

    float t = -( b_cos_phi - sqrt( ( b_len_sq * ( cos_phi_sq - 1 ) ) + r_sq ) ) / a_len;

    return r0 + a * t;
}

sf::Color
Sphere::GetColor() const
{
    return color_;
}

Vector
Sphere::GetCenter() const
{
    return center_;
}

float
Sphere::GetRadius() const
{
    return radius_;
}

} // namespace geometry
