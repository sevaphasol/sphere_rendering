#include "render/light.hpp"
#include "geometry/vector.hpp"
#include <iostream>

namespace render {

Light::Light( const geometry::Vector& pos,
              float                   embedded_intensity,
              float                   diffuse_intensity,
              float                   glare_intensity )
    : pos_( pos ), embedded_intensity_( embedded_intensity ),
      diffuse_intensity_( diffuse_intensity ), glare_intensity_( glare_intensity ) {};

void
Light::Move( const geometry::Vector& delta )
{
    pos_ += delta;
}

geometry::Vector
Light::CalcLight( const geometry::Vector& view,
                  const geometry::Vector& point,
                  const geometry::Vector& normal,
                  const sf::Color&        color ) const
{
    geometry::Vector light_ray = point - pos_;

    geometry::Vector embedded_light = CalcEmbeddedLight( color );
    geometry::Vector diffuse_light =
        CalcDiffuseLight( light_ray, normal ) * geometry::Vector( 1, 1, 1 );
    geometry::Vector glare_light =
        CalcGlareLight( light_ray, normal, view ) * geometry::Vector( 1, 1, 1 );

    return embedded_light + diffuse_light + glare_light;
}

geometry::Vector
Light::CalcEmbeddedLight( const geometry::Vector& color ) const
{
    return color * embedded_intensity_;
}

float
Light::CalcDiffuseLight( const geometry::Vector& light_ray, const geometry::Vector& normal ) const
{
    float cos       = -CalcCos( light_ray, normal );
    float intensity = diffuse_intensity_ * cos;

    return std::max( 0.0f, intensity * 255 );
}

float
Light::CalcGlareLight( const geometry::Vector& light_ray,
                       const geometry::Vector& normal,
                       const geometry::Vector& view ) const
{
    geometry::Vector reflected_ray = CalcReflectedRay( light_ray, normal );

    float cos       = -CalcCos( view, reflected_ray );
    float intensity = glare_intensity_ * float( std::pow( cos, 11 ) );

    return std::max( 0.0f, intensity * 255 );
}

geometry::Vector
CalcReflectedRay( const geometry::Vector& light_ray, const geometry::Vector& normal )
{
    return light_ray + normal * 2;
}

} // namespace render
