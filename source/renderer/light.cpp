#include "render/light.hpp"

namespace render {

Light::Light( const geometry::Vector& pos, float intensity )
    : pos_( pos ), intensity_( intensity ) {};

float
Light::CalcLumacy( const geometry::Vector& view,
                   const geometry::Vector& point,
                   const geometry::Vector& normal ) const
{
    geometry::Vector light_ray = point - pos_;

    return CalcDiffuseLumacy( light_ray, normal ) + CalcGlareLumacy( light_ray, normal, view );
}

float
Light::CalcDiffuseLumacy( const geometry::Vector& light_ray, const geometry::Vector& normal ) const
{
    return std::max( 0.0f, intensity_ * -CalcCos( light_ray, normal ) );
}

float
Light::CalcGlareLumacy( const geometry::Vector& light_ray,
                        const geometry::Vector& normal,
                        const geometry::Vector& view ) const
{
    geometry::Vector reflected_ray = CalcReflectedRay( light_ray, normal );

    return std::max( 0.0f, intensity_ * -CalcCos( view, reflected_ray ) );
}

geometry::Vector
CalcReflectedRay( const geometry::Vector& light_ray, const geometry::Vector& normal )
{
    return light_ray + normal * 2;
}

} // namespace render
